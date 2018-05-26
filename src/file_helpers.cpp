#include <iostream>
#include <fstream>
#include "assert.h"

#include "file_helpers.h"
#include "ppmloader/ppmloader.h"

unordered_map<string, unsigned int> dataset_train_file_to_map(string filename) {
    unordered_map<string, unsigned int> ret;
    std::fstream fs;
    fs.open(filename);
    while ( true ) {
        string key, tmp;
        unsigned int value;
        fs >> key >> tmp;
        if (!fs.good()){
            break;
        }

        value = atoi(tmp.substr(0, tmp.size()-1).c_str());
        std::pair<std::string,unsigned int> par (key.substr(0, key.size()-1), value);

        ret.insert(par);
    }
    fs.close();
    return ret;
}

vector<string> dataset_test_file_to_vector(string filename) {
    vector<string> ret;
    std::fstream fs;
    fs.open(filename);
    while ( true ) {
        string tmp;
        fs >> tmp;
        if (!fs.good()){
            break;
        }
        string key = tmp.substr(0, tmp.size()-1);
        ret.push_back(key);
    }
    fs.close();
    return ret;
}


void data_map_split(unordered_map<string, unsigned int>& mapa, Matrix& matrix, vector<int>& clasif) {
    for(auto it = mapa.begin(); it != mapa.end(); it++) {
        string filename = it->first;
		PGMImage img;
		img.load(filename);

		matrix.push_row(img.data_to_vec());
		clasif.push_back((int) it->second);
    }
	assert(matrix.n == (int) clasif.size());
}

vector<string> get_files(string filename){
  vector<string> files;
  std::fstream fs; fs.open(filename);
  while(true) {
      string file;
      fs >> file;
      if(!fs.good()){
        break;
      }
      files.push_back(file.substr(0, file.size()-1));
      fs >> file; //tira el resto de la fila
  }
  return files;
}
