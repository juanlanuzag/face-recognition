#ifndef _XVAL_H_
#define _XVAL_H_

#include "matrix.h"
#include <vector>

class XVal {
public:
	XVal(int n_folds = 3, bool shuffle = false, bool strat = true);
	void get_folds(Matrix A, vector<int> y, vector<vector<int> >& test_set, vector<vector<int> >& val_set);
	int get_n();
private:
	bool strat;
	bool shuffle;
	int n_folds;
};

#endif
