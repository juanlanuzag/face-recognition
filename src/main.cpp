#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include "assert.h"

#include "file_helpers.h"
#include "matrix.h"
#include "ppmloader/ppmloader.h"

using namespace std;

int method; //0: kNN, 1: PCA + kNN
string train_set_path;
string test_set_path;
string clasif_path;

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
		}
	}

	/********* LEO LOS ARCHIVOS PASADOS POR INPUT Y LOS CARGO EN MAPS *********/
	unordered_map<string, unsigned int> train_set = dataset_file_to_map(train_set_path);
	unordered_map<string, unsigned int> test_set = dataset_file_to_map(test_set_path);

	/********* PASO IMAGENES DE ENTRENAMIENTO A UNA MATRIZ *********/
	Matrix matriz;
	for(auto it = train_set.begin(); it != train_set.end(); it++) {
        string filename = it->first;
		PGMImage img;
		img.load(filename);

		matriz.push_row(img.data_to_vec());
    }
	cout << matriz.n << " " << matriz.m << endl;


	return 0;
}
