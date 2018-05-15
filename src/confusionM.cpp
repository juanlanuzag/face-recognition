#include <vector>
#include <iostream>

#include "confusionM.h"

using namespace std;

ConfusionM::ConfusionM(int size): conf(vector<vector<int>>(size, vector<int>(size, 0))), total(0) {};

void ConfusionM::update(int actual, int predicted){
	this->conf[actual][predicted]++;
	this->total++;
}

double ConfusionM::precision(int pos_class){
	double tp = this->conf[pos_class][pos_class];
	double fp = 0;

	for(int i = 0; i < this->conf.size(); i++){
		if(i != pos_class) fp += this->conf[i][pos_class];
	}

	return tp / (tp + fp);
}

double ConfusionM::recall(int pos_class){
	double tp = this->conf[pos_class][pos_class];
	double fn = 0;

	for(unsigned int i = 0; i < this->conf.size(); i++){
		if(i != pos_class) fn += this->conf[pos_class][i];
	}

	return tp / (tp + fn);
}

double ConfusionM::accuracy(){
	double correct = 0;
	for(int i = 0; i < conf.size(); i++){
		correct += this->conf[i][i];
	}

	return correct/this->total;
}

double ConfusionM::f1_score(int pos_class){
	double pres   = this->precision(pos_class);
	double recall = this->recall(pos_class);

	return 2 * pres * recall / (pres + recall);
}

ostream& operator<<(ostream& os, const ConfusionM c){
	for(int i = 0; i < c.conf.size(); i++){
		for(int j = 0; j < c.conf.size() - 1; j++){
			os << c.conf[i][j] << " ";
		}
		os << c.conf[i][c.conf.size() - 1];

		if(i < c.conf.size() - 1) os << endl; 
	}
	return os;
}
