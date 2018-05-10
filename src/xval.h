#ifndef _XVAL_H_
#define _XVAL_H_

#include "matrix.h"
#include <vector>

class XVal {
public:
	XVal(int n_folds = 3, bool shuffle = false, bool strat = true);
	vector<vector<int> > get_folds(vector<string>& files, vector<int>& y);
	int get_n();
private:
	bool strat;
	bool shuffle;
	int n_folds;
};

#endif
