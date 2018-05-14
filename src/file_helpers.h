#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H

#include <unordered_map>
#include <string>
#include <cstring>
#include <vector>

#include "matrix.h"

using namespace std;

unordered_map<string, unsigned int> dataset_file_to_map(string filename);

void data_map_split(unordered_map<string, unsigned int>& map, Matrix& matrix, vector<int>& clasif);

#endif //FILE_HELPERS_H
