#ifndef _XVAL_H_
#define _XVAL_H_

#include "matrix.h"
#include <vector>

struct Dataset {
	Matrix data;
	vector<int> tags;
};

class XVal {
public:
	XVal(Dataset& data, int n_folds = 3, bool shuffle = false, bool strat = true);

	vector<vector<int> > get_folds();

	int get_n();
	
	bool generate_data(Dataset& training, Dataset& validation);

private:
	bool strat;
	bool shuffle;
	int n_folds;

	Dataset data;
	vector<vector<int>> folds;
	vector<int>::iterator train_fold;

	void expand_data(Dataset& d, vector<int>& idxs);
};

#endif
