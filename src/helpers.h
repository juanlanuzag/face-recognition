#include "matrix.h"
#include <assert.h>

#ifndef PAGERANK_TP_HELPERS_H
#define PAGERANK_TP_HELPERS_H

double powerIteration(Matrix &a, int maxIterations, vector<double> &y);

vector<double> random_vector(int i);

Matrix deflation(Matrix const &a, int k);

Matrix calculateCovMatrix(Matrix &matrix);

vector<double> calulateMedian(Matrix &matrix);

#endif //PAGERANK_TP_HELPERS_H
