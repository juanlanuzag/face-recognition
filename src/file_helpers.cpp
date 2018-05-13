#include <iostream>
#include <fstream>
#include "assert.h"
#include "file_helpers.h"

unordered_map<string, unsigned int> dataset_file_to_map(string filename) {
    unordered_map<string, unsigned int> ret;
    std::fstream fs;
    fs.open(filename);
    while ( fs.good() ) {
        string key, tmp;
        unsigned int value;
        fs >> key >> tmp;
        value = atoi(tmp.substr(0, tmp.size()-1).c_str());
        std::pair<std::string,unsigned int> par (key.substr(0, key.size()-1), value);
        ret.insert(par);
    }
    fs.close();
    return ret;
}
