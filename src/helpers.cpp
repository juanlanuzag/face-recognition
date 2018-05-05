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


vector<double> operator*(Matrix &matrix, vector<double> &x) {
    //aca tomo al vector como vector columna
    assert(matrix.m == x.size());
    vector<double> prod(matrix.n, 0);
    for (unsigned int i = 0; i < matrix.n; i++) {
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
    assert(x.size() == matrix.n);
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

vector<double> random_vector(int i) {
    vector<double> vector(i, 0);
    for (int j = 0; j < i; ++j) {
        vector[j] = rand() / 10;
    }
    return vector;
}

Matrix transposedProduct(vector<double> x) {
    // Hace v * v^t
    Matrix matrix(x.size(), x.size());
    for (int i = 0; i < x.size(); ++i) {
        for (int j = 0; j < x.size(); ++j) {
            matrix[i][j] = x[i] * x[j];
        }
    }
    return matrix;
}

vector<double> deflation(Matrix const &a) {
    //Supongo que la Matrix es cuadrada y cumple con la condicion
    double dominant_eigenvalue;
    vector<double> y;
    Matrix b = a;
    vector<double> eigenvalues;
    for (int i = 0; i < a.n; ++i) {
        y = random_vector(a.n);
        dominant_eigenvalue = powerIteration(b, 1000, y);
        eigenvalues.push_back(dominant_eigenvalue);
        Matrix aux = transposedProduct(y);
        aux = dominant_eigenvalue * aux;
        b = b - aux;
    }
    return eigenvalues;
}