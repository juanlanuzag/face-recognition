#ifndef _KNN_H_
#define _KNN_H_

#include "matrix.h"

class KNN {
	public:
		KNN(Matrix& A, vector<int>& y, int n_neigh);

		int predict(vector<double>& v);

		double p_predict(vector<double>& v, char metric='a');

		double score(Matrix& A, vector<int>& y, char metric='a');

	private:
		Matrix data;
		vector<int> tags;
		int k;
};
#endif