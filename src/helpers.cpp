#include <assert.h>
#include <math.h>       /* sqrt */

#include "helpers.h"


double euclidianNorm(vector<double> &x) {
    double sum = 0;
    for (unsigned int i = 0; i < x.size(); i++) {
        sum += x[i] * x[i];
    }
    return sqrt(sum);
}

void normalize(vector<double> &x) {
    double norm = euclidianNorm(x);
    for (unsigned int i = 0; i < x.size(); i++) {
        x[i] = x[i] / norm;
    }
}

double dot_product(vector<double> x, vector<double> &y) {
    assert(x.size() == y.size());
    double sum = 0;
    for (unsigned int i = 0; i < x.size(); i++) {
        sum += x[i] * y[i];
    }
    return sum;
}

vector<double> operator-(vector<double> &x, vector<double> &y) {
    //aca tomo al vector como vector columna
    assert(x.size() == y.size());
    vector<double> res(x.size(), 0);
    for (unsigned int i = 0; i < x.size(); i++) {
        res[i] = x[i] - y[i];
    }
    return res;
}


vector<double> operator*(Matrix &matrix, vector<double> &x) {
    //aca tomo al vector como vector columna
    assert(matrix.m == (int) x.size());
    vector<double> prod(matrix.n, 0);
    for (int i = 0; i < matrix.n; i++) {
        double aux = 0;
        for (int j = 0; j < matrix.m; ++j) {
            aux += matrix[i][j] * x[j];
        }
        prod[i] = aux;
    }
    return prod;
}

vector<double> operator*(vector<double> &x, Matrix &matrix) {
    //aca tomo al vector como el vector transpuesto
    assert((int) x.size() == matrix.n);
    vector<double> sum(matrix.m);
    for (unsigned int i = 0; i < x.size(); i++) {
        double aux = 0;
        for (int j = 0; j < matrix.n; ++j) {
            aux += x[i] * matrix[j][i];
        }
        sum[i] = aux;
    }
    return sum;
}

//Calcula el autovalor maximo y su autovector asociado
double powerIteration(Matrix &a, int maxIterations, vector<double> &y) {
    // supongo que y esta bien elegido (si es random hay menos chances de que no converga la funcion)
    double res = 0;
    for (int i = 0; i < maxIterations; i++) {
        y = a * y;
        normalize(y); // normaliza por la norma euclida
        auto aux = a * y;
        res = dot_product(y, aux) / dot_product(y, y);
    }
    return res;
}

vector<double> randomVector(int i) {
    vector<double> vector(i, 0);
    for (int j = 0; j < i; ++j) {
        vector[j] = rand() / 10;
    }
    return vector;
}

Matrix transposedProduct(vector<double> x) {
    // Hace v * v^t
    Matrix matrix(x.size(), x.size());
    for (unsigned int i = 0; i < x.size(); ++i) {
        for (unsigned int j = 0; j < x.size(); ++j) {
            matrix[i][j] = x[i] * x[j];
        }
    }
    return matrix;
}

Matrix deflation(Matrix const &a, int k) {
    //Supongo que la Matrix es cuadrada y cumple con la condicion
    Matrix eigenvectors(k, a.m);
    double dominant_eigenvalue;
    Matrix b = a;
    Matrix d(a.n, a.m);
    for (int i = 0; i < k; ++i) {
        vector<double> y = randomVector(a.n);
        dominant_eigenvalue = powerIteration(b, 1000, y);
        eigenvectors[i] = y; // Guardo el autovector asociado al i-esimo autovalor
        d[i][i] = dominant_eigenvalue;
        Matrix aux = transposedProduct(y);
        aux = dominant_eigenvalue * aux;
        b = b - aux;
    }
    return eigenvectors;
}


Matrix pca(Matrix &a, int alpha) {
    Matrix covMatrix = calculateCovMatrix(a); //Calculo la Matriz de Covarianza
    Matrix v = deflation(covMatrix, alpha); // Ya esta transpuesto la matrix de las alpha componentes principales
    Matrix x = a.transpose();
    x = v * x;
    Matrix b = x.transpose(); // Diagonalizo, elijo alpha componentes principales y Cambio de base
    return b;
}

Matrix calculateCovMatrix(Matrix &matrix) {
    Matrix x(matrix.n, matrix.m);
    vector<double> median = calulateMedian(matrix);
    for (int i = 0; i < matrix.n; ++i) {
        x[i] = matrix[i] - median;
    }
    Matrix transposed = x.transpose();
    double aux = 1.0 / (matrix.n - 1);
    Matrix covMatrix = transposed * x;
    covMatrix = aux * covMatrix;
    return covMatrix;
}

vector<double> calulateMedian(Matrix &matrix) {
    vector<double> median(matrix.m, 0);
    for (int i = 0; i < matrix.n; ++i) {
        for (int j = 0; j < matrix.m; ++j) {
            median[j] += matrix[i][j] / matrix.n;
        }
    }
    return median;
}
