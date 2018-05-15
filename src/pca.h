#ifndef _PCA_H
#define _PCA_H

#include "matrix.h"

// Al crearse la clase se calcula la matrix transformada
// se guarda las componentes principales para realizar la transformacion caracterictica de una muestra
class PCA {
public:
    //La matriz transformada
    Matrix fitMatrix;

    PCA(Matrix &a, int alpha);

    vector<double> tc(vector<double> &x);

private:
    Matrix calculateRelatedMatrix(Matrix &matrix);
    Matrix v;
    Matrix x;
    vector<double> median;
};

vector<double> randomVector(int i);

Matrix deflation(Matrix const &a, int k);

double powerIteration(Matrix &a, int maxIterations, vector<double> &y);

void normalize(vector<double> &x);

vector<double> calulateMedian(Matrix &matrix);

double euclidianNorm(vector<double> &x);

double dot_product(vector<double> x, vector<double> &y);

Matrix transposedProduct(vector<double> x);

#endif //_PCA_H
