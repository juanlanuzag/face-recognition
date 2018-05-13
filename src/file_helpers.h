#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H

#include <unordered_map>
#include <string>
#include <cstring>

using namespace std;

unordered_map<string, unsigned int> dataset_file_to_map(string filename);

#endif //FILE_HELPERS_H
