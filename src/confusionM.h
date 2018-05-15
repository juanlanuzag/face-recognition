#ifndef _CONFUSIONM_H_
#define _CONFUSIONM_H_

#include <vector>
#include <iostream> 

using namespace std;

class ConfusionM {
	public:
		ConfusionM(int size);

		void update(int actual, int predicted);

		double precision(int pos_class);

		double recall(int pos_class);

		double accuracy();

		double f1_score(int pos_class);

		friend ostream& operator<<(ostream& os, const ConfusionM c);

	private:
		vector<vector<int> > conf;

		double total;
};

#endif
