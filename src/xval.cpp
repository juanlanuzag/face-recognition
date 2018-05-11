#include "xval.h"
#include <algorithm>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

XVal::XVal(int n_folds, bool shuffle, bool strat): n_folds(n_folds), shuffle(shuffle), strat(strat){}

int XVal::get_n(){ return this->n_folds; }

vector<vector<int>> XVal::get_folds(vector<string>& files, vector<int>& y){
	int fold_size = y.size() / this->n_folds;
	
	vector<int> idxs;
	vector<vector<int>> kfolds;

	for(int i = 0; i < y.size(); i++){
		idxs.push_back(i);
	}

	if(this->shuffle){
		srand(time(0));
		random_shuffle(idxs.begin(), idxs.end());
	}

	if(this->strat){
		map<int, vector<int>> class_bucket;
		for(int idx : idxs){
			class_bucket[y[idx]].push_back(idx);
		}

		kfolds = vector<vector<int>>(this->n_folds, vector<int>());
		int cur_fold = 0;
		for(auto bucket : class_bucket){
			for(auto idx : bucket.second){
				kfolds[cur_fold].push_back(idx);
				cur_fold = (cur_fold + 1) % this->n_folds;
			}
		}
	} else {
		int i = 0;
		int r = y.size() % this->n_folds;
		while(i < idxs.size()){
			vector<int>fold;
			for(int j = 0; j < fold_size; j++){
				if(i < idxs.size()){
					fold.push_back(idxs[i]);
					i++;
				}
			}
			if(r > 0){
				fold.push_back(idxs[i]);
				i++;
			}

			kfolds.push_back(fold);
		}	

	}	

	return kfolds; 
}
