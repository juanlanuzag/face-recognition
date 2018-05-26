#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include "assert.h"
#include <fstream>
#include <chrono>
#include <algorithm>

#include "file_helpers.h"
#include "matrix.h"
#include "knn.h"
#include "pca.h"
#include "ppmloader/ppmloader.h"
#include "confusionM.h"
#include "xval.h"
using namespace std;

int method = -1; //0: kNN, 1: PCA + kNN
string train_set_path = "";
string test_set_path = "";
string clasif_path = "";
int knn_k = 3;
int alpha = 17;
int n_folds = 0;
bool strat = true;
extern int maxIterations;
extern bool printEigenvalues;
extern bool saveEigenvector;

int main(int argc, char *argv[]){
	// ./main -m 1 -i train.csv -q test.csv -o result.csv

	/********* LEO EL INPUT *********/
	for(int i = 1; i < argc; i++) {
		if(strcmp(argv[i], "-m") == 0) {
			method = atoi(argv[i+1]);
		} else if(strcmp(argv[i], "-i") == 0) {
			train_set_path = argv[i+1];
		} else if(strcmp(argv[i], "-q") == 0) {
			test_set_path = argv[i+1];
		} else if(strcmp(argv[i], "-o") == 0) {
			clasif_path = argv[i+1];
		} else if(strcmp(argv[i], "-knn-k") == 0) {
			knn_k = atoi(argv[i+1]);
		}  else if(strcmp(argv[i], "-alpha") == 0) {
			alpha = atoi(argv[i+1]);
		}  else if(strcmp(argv[i], "-max-it") == 0) {
			maxIterations = atoi(argv[i+1]);
		}  else if(strcmp(argv[i], "--autoval") == 0) {
            // imprime los autovalores en cada iteracion del metodo de potencias
            printEigenvalues = true;
        }  else if(strcmp(argv[i], "--autoimg") == 0) {
            // Guarda los Autovectores como imagenes
            saveEigenvector = true;
        } else if(strcmp(argv[i], "-k-folds") == 0) {
			n_folds = atoi(argv[i+1]);
		} else if (strcmp(argv[i], "-strat") == 0){
			strat = atoi(argv[i+1]);
		} else if(strcmp(argv[i], "--help") == 0) {
			cout << "Parametros para correr el comando ./main :" << endl;
			cout << "-m  Method (0: knn solo, 1: knn + pca)" << endl;
			cout << "-i  Path al archivo con el train_set" << endl;
			cout << "-q  Path al archivo con el test_set" << endl;
			cout << "-o  Path del archivo de salida con la clasificacion de los datos de test_set" << endl;
			cout << "-knn-k indica el k a usar en knn (default 3)" << endl;
			cout << "-alpha indica el alpha a usar en pca (default 17)" << endl;
			cout << "-k-folds indica la cantidad de folds que se usan para cross validation (default no se usa xval)" << endl;
			return 0;
		}
	}
	/********* VALIDACIONES DE LOS INPUT *********/
	if (method == -1) {
		cout << "Error, se debe pasar el parametro -m con el metodo a utilizar" << endl;
		return 1;
	}
	if (method == 0 && (train_set_path.size() == 0 || test_set_path.size() == 0)) {
		cout << "Para el metodo knn se debe pasar tanto archivo de train como de test" << endl;
		return -1;
	}
	if ((method == 2 || method == 3) && (n_folds < 2 || n_folds > train_set_path.size())) {
		cout << "Mala cantidad de folds (debe ser 2 < n_folds < size(dataset)" << endl;
	}

	/********* LEO ARCHIVO PASADO POR INPUT Y LO CARGO EN MAP *********/
	unordered_map<string, unsigned int> train_set = dataset_train_file_to_map(train_set_path);
	/********* PASO IMAGENES DE ENTRENAMIENTO A UNA MATRIZ Y RESULTADOS A UN VECTOR *********/
	Dataset train;
	data_map_split(train_set, train.data, train.tags);

	Dataset val;
	vector<string> test_set;
	vector<vector<double> > test_imgs;

	if(method==0 || method==1){
			unordered_map<string, unsigned int> val_set = dataset_train_file_to_map(test_set_path);
			data_map_split(val_set, val.data, val.tags);
	} else {
		/********* LEO ARCHIVO PASADO POR INPUT Y LO CARGO EN VECTOR *********/
		test_set = dataset_test_file_to_vector(test_set_path);
		/********* PASO IMAGENES DE TEST A UNA MATRIZ Y RESULTADOS A UN VECTOR *********/
		for (unsigned int i=0; i < test_set.size(); i++) {
			test_imgs.push_back(imgvec_from_filepath(test_set[i]));
		}
	}

	if (method == 0) {
		// KNN solo
		KNN knn(train.data, train.tags, knn_k); // Aca entrena
		fstream fs(clasif_path, fstream::in | fstream::out | fstream::trunc);

		// auto start = std::chrono::high_resolution_clock::now();

		vector<string> files = get_files(test_set_path);


		for (unsigned int i=0; i < files.size(); i++) {
			fs << files[i] << ", " << knn.predict(val.data[i]) << "," << endl;
		}

		ConfusionM c = knn.score(val.data, val.tags);

		cout << "method,train_set,val_set,knn-k,accuracy" << endl;
		cout << method << "," << train_set_path << "," << test_set_path << "," << knn_k  << "," << c.accuracy() << "," << endl;

		// auto end = std::chrono::high_resolution_clock::now();
		// auto elapsed = std::chrono::duration_cast<chrono::duration<double>>(end - start);
		// cout << knn_k << ", " << elapsed.count() << endl;

		fs.close();

	} else if (method == 1) {
		vector<string> files = get_files(test_set_path);

		// PCA + KNN
		PCA pca(train.data, alpha);
		KNN knn(pca.fitMatrix, train.tags, knn_k); // Aca entrena

		fstream fs(clasif_path, fstream::in | fstream::out | fstream::trunc);
		for (unsigned int i=0; i < files.size(); i++) {
    		auto v = pca.tc(val.data[i]);
				fs << files[i] << ", " << knn.predict(v) << "," << endl;
		}

		fs.close();
		Matrix transformed_v_data;
		for(unsigned int i = 0; i < val.data.n; i++){
			auto vec = pca.tc(val.data[i]);
			transformed_v_data.push_row(vec);
		}
		ConfusionM c = knn.score(transformed_v_data, val.tags);

		cout << "method,train_set,val_set,knn-k,alpha,accuracy" << endl;
		cout << method << "," << train_set_path << "," << test_set_path << "," << knn_k << "," << alpha << "," << c.accuracy() << "," << endl;

	} else if (method == 2) {
		Dataset t,v;

		XVal split = XVal(train, n_folds, true, strat);

		int iteration = 0;

		fstream fs(clasif_path, fstream::in | fstream::out | fstream::trunc);
		fs << "method,train_set,knn-k,k-folds,test_fold,acccuracy" << endl;

		fstream fs2(clasif_path+".conf", fstream::in | fstream::out | fstream::trunc);
		fs2 << *max_element(train.tags.begin(), train.tags.end()) << " " << n_folds << endl;

		while(split.generate_data(t, v)){
			KNN knn(t.data, t.tags, knn_k);
			ConfusionM c = knn.score(v.data, v.tags);
			fs2 << c << endl;
			fs << method << "," << train_set_path << "," << knn_k << "," << n_folds << "," << iteration++ << "," << c.accuracy() << endl;
		}
	} else if (method == 3) {
		Dataset t,v;
		XVal split = XVal(train, n_folds, true, strat);

		int iteration = 0;

		fstream fs(clasif_path, fstream::in | fstream::out | fstream::trunc);
		fs << "method,train_set,knn-k,k-folds,alpha,test_fold,accuracy" << endl;

		fstream fs2(clasif_path+".conf", fstream::in | fstream::out | fstream::trunc);
		fs2 << *max_element(train.tags.begin(), train.tags.end()) << " " << n_folds << endl;

		while(split.generate_data(t, v)){
			PCA pca(t.data, alpha);
			KNN knn(pca.fitMatrix, t.tags, knn_k);

			Matrix transformed_v_data;
			for(unsigned int i = 0; i < v.data.n; i++){
				auto vec = pca.tc(v.data[i]);
				transformed_v_data.push_row(vec);
			}
			ConfusionM c = knn.score(transformed_v_data, v.tags);

			fs2 << c << endl;
			fs << method << "," << train_set_path << "," << knn_k << "," << n_folds << "," << alpha << "," << iteration++ << "," << c.accuracy() << endl;
		}

	}
	return 0;
}
