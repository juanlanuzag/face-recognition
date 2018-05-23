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

int main(int argc, char* argv[]){
  string train_set_path = argv[1];
  string dim_reduc_out = argv[2];

  unordered_map<string, unsigned int> train_set = dataset_train_file_to_map(train_set_path);

  Dataset train;
  data_map_split(train_set, train.data, train.tags);
  for(int t : train.tags){
    cout << t << ",";
  }
  PCA pca(train.data, 3);
  fstream fs(dim_reduc_out, fstream::in | fstream::out | fstream::trunc);
  fs << pca.fitMatrix;
  for(auto tag: train.tags){
    fs << tag << " ";
  }
  fs.close();

  return 0;
}
