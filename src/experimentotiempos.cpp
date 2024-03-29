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
int knn_k = 1;
int alpha = 1;
int n_folds = 0;

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
		} else if(strcmp(argv[i], "-k-folds") == 0) {
			n_folds = atoi(argv[i+1]);
		} else if(strcmp(argv[i], "--help") == 0) {
			cout << "Parametros para correr el comando ./main :" << endl;
			cout << "-m  Method (0: knn solo)" << endl;
			cout << "-i  Path al archivo con el train_set" << endl;
			cout << "-q  Path al archivo con el test_set" << endl;
			cout << "-o  Path del archivo de salida con la clasificacion de los datos de test_set" << endl;
			cout << "-knn-k indica el k a usar en knn (default 1)" << endl;
			cout << "-alpha indica el alpha a usar en pca (default 1)" << endl;
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

	/********* LEO ARCHIVO PASADO POR INPUT Y LO CARGO EN VECTOR *********/
	vector<string> test_set = dataset_test_file_to_vector(test_set_path);
	/********* PASO IMAGENES DE TEST A UNA MATRIZ Y RESULTADOS A UN VECTOR *********/
	vector<vector<double> > test_imgs;
	for (unsigned int i=0; i < test_set.size(); i++) {
		test_imgs.push_back(imgvec_from_filepath(test_set[i]));
	}

	if (method == 0) {
        KNN knn(train.data, train.tags, knn_k); // Aca entrena
        double totalTimeElapsed = 0;

        for (int t = 0; t < 10; t++) {
            auto start = std::chrono::high_resolution_clock::now();
            for (unsigned int i=0; i < test_imgs.size(); i++) {
                knn.predict(test_imgs[i]);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<chrono::duration<double>>(end - start);
            totalTimeElapsed += elapsed.count();
        }

        cout << totalTimeElapsed / 10 << endl;

	} else if (method == 1) {
		// PCA + KNN
		double totalTimePCA = 0;
		// for (int t = 0; t < 10; t++) {
        //     auto start = std::chrono::high_resolution_clock::now();
		//
		// 	PCA pca(train.data, alpha);
		//
		// 	auto end = std::chrono::high_resolution_clock::now();
        //     auto elapsed = std::chrono::duration_cast<chrono::duration<double>>(end - start);
        //     totalTimePCA += elapsed.count();
        // }
		PCA pca(train.data, alpha);
		KNN knn(pca.fitMatrix, train.tags, knn_k); // Aca entrena

		double totalTimePredict = 0;
		for (int t = 0; t < 10; t++) {
            auto start = std::chrono::high_resolution_clock::now();

			for (unsigned int i=0; i < test_imgs.size(); i++) {
				auto v = pca.tc(test_imgs[i]);
				knn.predict(v);
			}

			auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<chrono::duration<double>>(end - start);
            totalTimePredict += elapsed.count();
        }
		cout << totalTimePCA/ 10 <<","<<totalTimePredict/ 10 << endl;
	}
	return 0;
}
