#include <vector>
#include "matrix.h"
#include <cassert>
#include <cmath>

double mu = 1e-8;

// Que acceden a estructura interna
Matrix::Matrix(int n, int m) : n(n), m(m), matrix(vector<vector<double> >(n, vector<double>(m, 0))) {}

pair<int, int> Matrix::dimensions() const {
    return make_pair(this->n, this->m);
}

Matrix Matrix::transpose() {
    Matrix transposed(m, n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

vector<double>& Matrix::operator[] (int i) {
    return matrix[i];
}

Matrix operator*(Matrix &m1, Matrix &m2) {
    int n = m1.n;
    int k = m1.m;
    int m = m2.m;
    assert(k == m2.n);
    Matrix prod(n, m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            double acum = 0;
            for(int l = 0; l < k; l++) {
                acum += m1[i][l] * m2[l][j];
            }
            prod[i][j] = acum;
        }
    }
    return prod;
}

Matrix operator+(Matrix &m1, Matrix &m2) {
    assert(m1.n == m2.n);
    assert(m1.m == m2.m);
    Matrix sum(m1.n, m1.m);
    for(int i = 0; i < m1.n; i++) {
        for(int j = 0; j < m1.m; j++) {
            sum[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return sum;
}

Matrix operator-(Matrix &m1, Matrix &m2) {
    assert(m1.n == m2.n);
    assert(m1.m == m2.m);
    Matrix sum(m1.n, m1.m);
    for(int i = 0; i < m1.n; i++) {
        for(int j = 0; j < m1.m; j++) {
            sum[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return sum;
}

Matrix operator*(double p, Matrix &m) {
    Matrix scprod(m.n, m.m);
    for(int i = 0; i < m.n; i++) {
        for(int j = 0; j < m.m; j++) {
            scprod[i][j] = p* m[i][j];
        }
    }
    return scprod;
}

ostream &operator<<(ostream &os, Matrix &matrix) {
    int n = matrix.dimensions().first;
    int m = matrix.dimensions().second;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            os << matrix[i][j] << "  ";
        }
        os << endl;
    }
    return os;
}

Matrix identity(int n) {
    Matrix id(n, n);
    for (int i = 0; i < n; ++i) {
        id[i][i] = 1;
    }
    return id;
}

// double euclidianNorm(vector<double> &x) {
//     double sum = 0;
//     for (unsigned int i = 0; i < x.size(); i++) {
//         sum += x[i] * x[i];
//     }
//     return sqrt(sum);
// }
//
// void normalize(vector<double> &y) {
//     double norm = euclidianNorm(y);
//     for (unsigned int i = 0; i < y.size(); i++) {
//         y[i] = y[i] / norm;
//     }
// }
//
// //Calcula el autovalor maximo y su autovector
// double powerIteration(Matrix &a, int maxIterations, vector<double> &y) {
//     // supongo que y esta bien elegido (si es random hay menos chances de que no converga la funcion)
//     double res = 0;
//     for (int i = 0; i < maxIterations; i++) {
//         y = a * y;
//         normalize(y); // normaliza por la norma euclida
//         vector<double> aux(a * y);
//         res = (aux * y) / (y * y);
//     }
//
//     return res;
// }
