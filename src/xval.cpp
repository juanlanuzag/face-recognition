#include "xval.h"
#include <algorithm>

using namespace std;

XVal(int n_folds, bool shuffle, bool strat): n_folds(n_folds), shuffle(shuffle), strat(strat){}

int XVal::get_n(){ return this->n_folds; }

void get_folds(Matrix& A, vector<int> y, vector<vector<int>>& test_set, vector<vector<int>>& val_set){
	int fold_size = y.size() / this->n_folds;
	
	vector<int> idxs = vector<int>(y.size(), 0);
	
	for(int i = 0; i < y.size(); i++){
		idxs.push_back(i);
	}

	if(this->shuffle){
		random_shuffle(idxs.begin(), idxs.end());
	}

	if(this->strat){
	
	} else {
	for(int k = 0; k < idxs.size(); k+=fold_size){
		vector<int> fold;
		for(int i = 0; i < fold_size; i++){
			if(k + i < idxs.size()) fold.push_back(idxs[k+i]);
		}	
	}

	return; 
}
