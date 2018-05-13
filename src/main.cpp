#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>

#include "file_helpers.h"

using namespace std;

int method; //0: kNN, 1: PCA + kNN
string train_set_path;
string test_set_path;
string clasif_path;

int main(int argc, char *argv[]){
	// ./main -m 1 -i train.csv -q test.csv -o result.csv

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

	unordered_map<string, unsigned int> train_set = dataset_file_to_map(train_set_path);


    for(auto it = train_set.begin(); it != train_set.end(); it++) {
        cout << it->first  << " " << it->second << endl;
    }
	// cout << "Method: " << method << endl;
	// cout << "Train Set Path " << train_set_path << endl;
	// cout << "Test Set Path " << test_set_path << endl;
	// cout << "Clasig Path " << clasif_path << endl;
	return 0;
}
