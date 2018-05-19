#include "xval.h"
#include <algorithm>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iterator>

using namespace std;

XVal::XVal(Dataset& data, int n_folds, bool shuffle, bool strat): data(data), n_folds(n_folds), shuffle(shuffle), strat(strat){
	this->get_folds();
}

int XVal::get_n(){ return this->n_folds; }

Dataset XVal:: get_data(){ return this->data; }

void XVal::get_folds(){
	//Computa y setea los folds de la estructura, setea train_fold

	vector<int> y = this->data.tags;
	int fold_size = y.size() / this->n_folds;
	
	vector<int> idxs;

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

		this->folds = vector<vector<int>>(this->n_folds, vector<int>());
		int cur_fold = 0;
		for(auto bucket : class_bucket){
			for(auto idx : bucket.second){
				this->folds[cur_fold].push_back(idx);
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

			this->folds.push_back(fold);
		}	
	}
	this->train_fold = this->folds.begin();
}

bool XVal::generate_data(Dataset& training, Dataset& validation){
	/*
	Genera el siguiente dataset para el modelo.
	IN:
		training -> donde se guardan los datos de training
		validation -> donde se guardan los datos de validacion
	OUT:
		false <==> ya se usaron todas las combinaciones de training/validation
	
	Idea de uso:
		while(generate_data(training, validation)){
			***testear***
		}
	*/	
	if(this->train_fold == this->folds.end()) {
		cout << "FINAL" << endl;
		return false;
	}
	Dataset empty;
	training = empty;
	validation = empty;

	for(vector<vector<int>>::iterator it = this->folds.begin(); it != this->folds.end(); it++){
		if(it != this->train_fold){
			expand_data(training, *it);
		} else {
			expand_data(validation, *it);
		}
	}
	cout << (++this->train_fold != this->folds.end()) << endl;
}

void XVal::expand_data(Dataset& d, vector<int>& idxs){
	for(int idx : idxs){
		d.data.push_row(this->data.data[idx]);
		d.tags.push_back(this->data.tags[idx]);
	}
}
