#include "matrix.h"
#include <assert.h>

#ifndef PAGERANK_TP_HELPERS_H
#define PAGERANK_TP_HELPERS_H

double powerIteration(Matrix &a, int maxIterations, vector<double> &y);

vector<double> random_vector(int i);

vector<double> deflation(Matrix const &a);

#endif //PAGERANK_TP_HELPERS_H
