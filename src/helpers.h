#ifndef PAGERANK_TP_HELPERS_H
#define PAGERANK_TP_HELPERS_H

#include "matrix.h"

Matrix pca(Matrix &a, int alpha);

Matrix deflation(Matrix const &a, int k);

double powerIteration(Matrix &a, int maxIterations, vector<double> &y);

void normalize(vector<double> &x);

Matrix calculateCovMatrix(Matrix &matrix);

vector<double> calulateMedian(Matrix &matrix);

vector<double> randomVector(int i);

double euclidianNorm(vector<double> &x);

double dot_product(vector<double> x, vector<double> &y);

Matrix transposedProduct(vector<double> x);

vector<double> operator*(Matrix &matrix, vector<double> &x);

vector<double> operator*(vector<double> &x, Matrix &matrix);

#endif //PAGERANK_TP_HELPERS_H
