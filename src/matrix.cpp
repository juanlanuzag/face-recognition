#include <vector>
#include "matrix.h"
#include <cassert>
#include <cmath>

double mu = 1e-8;

// Que acceden a estructura interna
Matrix::Matrix(int n, int m) : n(n), m(m), matrix(unordered_map<int, unordered_map<int, double> >()) {}

Matrix::Matrix(int n) : n(n), m(n), matrix(unordered_map<int, unordered_map<int, double> >()) {}

double Matrix::getElem(int i, int j) const {
    //Busco el elemento (i,j) si no se encuentra en la estructura interna entonces el valor es 0
    if (matrix.find(i) != matrix.end()) {
        if (matrix.find(i)->second.find(j) != matrix.find(i)->second.end()) {
            return matrix.find(i)->second.find(j)->second;
        }
    }
    return 0;
}

void Matrix::setElem(int i, int j, double val) {
    //Si el valor es mayor al umbral lo considero
    if (abs(val) > mu) {
        this->matrix[i][j] = val;
    } else {
        //Si es menor o igual al mu lo elimino de la estructura interna por ser considerado 0
        if (matrix.find(i) != matrix.end() and matrix.find(i)->second.find(j) != matrix.find(i)->second.end()) {
            matrix[i].erase(j);
        }
    }
}

pair<int, int> Matrix::dimensions() const {
    return make_pair(this->n, this->m);
}

Matrix operator*(const Matrix &m1, const Matrix &m2) {
    int n_prod = m1.dimensions().first;
    int m_prod = m2.dimensions().second;
    int mid_dim = m1.dimensions().second;
    assert (mid_dim == m2.dimensions().first);

    Matrix prod(n_prod, m_prod);
    //Itera por las filas de de m1
    for (unordered_map<int, unordered_map<int, double> >::const_iterator it = m1.matrix.begin();
         it != m1.matrix.end(); it++) {
        for (int j = 0; j < m_prod; j++) {
            double sum = 0;
            //Itera sobre la fila
            for (unordered_map<int, double>::const_iterator it_row = it->second.begin();
                 it_row != it->second.end(); it_row++) {
                // it_row->first es la columna del elemento que estamos iterando
                sum += it_row->second * m2.getElem(it_row->first, j);
            }
            prod.setElem(it->first, j, sum);
        }
    }
    return prod;
}

Matrix operator+(const Matrix &a, const Matrix &b) {
    int n1 = a.dimensions().first;
    int m1 = a.dimensions().second;
    int n2 = b.dimensions().first;
    int m2 = b.dimensions().second;
    assert(n1 == n2);
    assert(m1 == m2);

    Matrix sum(n1, m1);

    for (int i = 0; i < m1; ++i) {
        for (int j = 0; j < n1; ++j) {
            sum.setElem(i, j, a.getElem(i, j) + b.getElem(i, j));
        }
    }
    return sum;
}

Matrix operator-(const Matrix &a, const Matrix &b) {
    int n1 = a.dimensions().first;
    int m1 = a.dimensions().second;

    int n2 = b.dimensions().first;
    int m2 = b.dimensions().second;

    assert(n1 == n2);
    assert(m1 == m2);

    Matrix sub(n1, m1);

    for (int i = 0; i < m1; ++i) {
        for (int j = 0; j < n1; ++j) {
            sub.setElem(i, j, a.getElem(i, j) - b.getElem(i, j));
        }
    }
    return sub;
}

Matrix operator*(double p, const Matrix &m) {
    int n = m.dimensions().first;
    int k = m.dimensions().second;
    Matrix prod(n, k);
    //Itero por los elementos distintos de 0
    for (unordered_map<int, unordered_map<int, double> >::const_iterator it = m.matrix.begin();
         it != m.matrix.end(); it++) {
        for (unordered_map<int, double>::const_iterator it_row = it->second.begin();
             it_row != it->second.end(); it_row++) {
            prod.setElem(it->first, it_row->first, it_row->second * p);
        }
    }
    return prod;
}

vector<double> operator*(const Matrix &a, const vector<double> &x) {
    vector<double> prod(x.size(), 0);
    for (int i = 0; i < a.dimensions().first; i++) {
        for (int j = 0; j < x.size(); j++) {
            prod[i] += a.getElem(i, j) * x[j];
        }
    }
    return prod;
}

ostream &operator<<(ostream &os, const Matrix &matrix) {
    int n = matrix.dimensions().first;
    int m = matrix.dimensions().second;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            os << matrix.getElem(i, j) << "  ";
        }
        os << endl;
    }
    return os;
}

Matrix identity(int n) {
    Matrix id(n);
    for (int i = 0; i < n; ++i) {
        id.setElem(i, i, 1);
    }
    return id;
}

double operator*(vector<double> const &x, vector<double> const &y) {
    double prod = 0;
    for (int i = 0; i < x.size(); i++) {
        prod += y[i] * x[i];
    }
    return prod;
}

double euclidianNorm(vector<double> &x) {
    double sum = 0;
    for (int i = 0; i < x.size(); i++) {
        sum += x[i] * x[i];
    }
    return sqrt(sum);
}

void normalize(vector<double> &y) {
    double norm = euclidianNorm(y);
    for (int i = 0; i < y.size(); i++) {
        y[i] = y[i] / norm;
    }
}

//Calcula el autovalor maximo y su autovector
double powerIteration(Matrix &a, int maxIterations, vector<double> &y) {
    // supongo que y esta bien elegido (si es random hay menos chances de que no converga la funcion)
    double res = 0;
    for (int i = 0; i < maxIterations; i++) {
        y = a * y;
        normalize(y); // normaliza por la norma euclida
        vector<double> aux(a * y);
        res = (aux * y) / (y * y);
    }

    return res;
}