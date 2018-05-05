#include "knn.h"
#include <cassert>
#include <math.h>
#include <map>
#include <set>

//Prototipo de func aux
double euclid_dist(vector<double>& v, vector<double>& w);


KNN::KNN(Matrix& A, vector<int>& y, int n_neigh = 10): k(n_neigh), data(A), tags(y)
{
	unsigned int n_tags = tags.size();
	unsigned int n_data = data.dimensions().first;
	assert(n_tags == n_data);
};

int KNN::predict(vector<double>& img){

	set<pair<double, double> > k_dists;
	map<double, int> votes;

	for(int i = 0; i < this->data.dimensions().first; i++){
		double tag = this->tags[i];
		double dist = euclid_dist(img, this->data[i]);
		if(k_dists.size() < this->k){
			k_dists.insert(make_pair(dist, tag));
			votes[tag]++;
		} else {
			auto last_elem = k_dists.rbegin();
			if(dist < last_elem->first){
				votes[last_elem->second]--;
				k_dists.erase(*last_elem);

				votes[tag]++;
				k_dists.insert(make_pair(dist, tag));
			}
		}
	}

	int max_tag = -1;
	int max_votes = 0;

	for(auto it : votes){
		if(it.second > max_votes){
			max_tag = it.first;
			max_votes = it.second;
		}
	}
	return max_tag;
}

double euclid_dist(vector<double>& v, vector<double>& w){
	assert(v.size() == w.size());
	double dist = 0;
	for(unsigned int i = 0; i < v.size(); i++){
		dist += pow (v[i] - w[i], 2);
	}
	return sqrt(dist);
}

double KNN::p_predict(vector<double>& v, char metric = 'a'){
	return 0;
}

double KNN::score(Matrix& A, vector<double>& y, char metric = 'a'){
	assert(A.dimensions().first == y.size());
	double res;

	switch(metric){
		case 'a':
		{
			double total = y.size();
			double correct = 0;
			for(int i = 0; i < A.dimensions().first; i++){
				int prediction = this->predict(A[i]);
				if(prediction == y[i]) correct++;
			}
			res = correct/total;
			break;
		}
		default:
		{
			res = -1;
			break;
		}
	}

	return res;
}
