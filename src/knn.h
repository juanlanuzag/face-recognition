#ifndef _KNN_H_
#define _KNN_H_

#include "matrix.h"
#include "confusionM.h"

class KNN {
	public:
		KNN(Matrix& A, vector<int>& y, int n_neigh);

		int predict(vector<double>& v);

		double p_predict(vector<double>& v, char metric='a');

		ConfusionM score(Matrix& A, vector<int>& y);

	private:
		int k;
		Matrix data;
		vector<int> tags;
};
#endif
