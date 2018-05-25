#include <assert.h>
#include <math.h>       /* sqrt */
#include <random>

#include "pca.h"
#include "ppmloader/ppmloader.h"

int maxIterations = 1000;
bool printEigenvalues = false;
bool saveEigenvector = false;

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
    vector<double> prod(matrix.m);
    for (unsigned int i = 0; i < x.size(); i++) {
        double aux = 0;
        for (int j = 0; j < matrix.n; ++j) {
            aux += x[i] * matrix[j][i];
        }
        prod[i] = aux;
    }
    return prod;
}

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

//Calcula el autovalor maximo y su autovector asociado
double powerIteration(Matrix &a, int maxIterations, vector<double> &y) {
    double res = 0;

    if (printEigenvalues) cout << "Calculando : " << endl; // Para un test
    for (int i = 0; i < maxIterations; i++) {
        y = a * y;
        normalize(y); // normaliza por la norma euclida
        auto aux = a * y;
        res = dot_product(y, aux) / dot_product(y, y);

        if (printEigenvalues) cout << res << endl;// Para un test
    }

    return res;
}

vector<double> randomVector(int i) {
    vector<double> vector(i, 0);    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(-10.0, 10.0);
    for (int j = 0; j < i; ++j) {
        vector[j] = dist(mt) / 10;
    }
    normalize(vector);
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
    for (int i = 0; i < k; ++i) {
        vector<double> y = randomVector(a.n);
        dominant_eigenvalue = powerIteration(b, maxIterations, y);
        eigenvectors[i] = y; // Guardo el autovector asociado al i-esimo autovalor
        Matrix aux = transposedProduct(y);
        aux = dominant_eigenvalue * aux;
        b = b - aux;
    }

    return eigenvectors;
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

PCA::PCA(Matrix &a, int alpha) {
    Matrix matrixC = calculateRelatedMatrix(a); //Calculo la Matriz Relacionada a la matriz de Covarianza -> X * X^t
    Matrix eigenvectors = deflation(matrixC, alpha); // Diagonalizo, elijo alpha componentes principales y
    Matrix transposed = x.transpose();

    // Transformo los autovectores de X * X^t a  los de la covarianza
    v = Matrix(alpha, a.m);
    for (int i = 0; i < alpha; ++i) {
        v[i] = transposed * eigenvectors[i];
    }

    if (saveEigenvector) {
        for (int i = 0; i < v.n; i++) {
            // Guardo los autovectores como imagenes
            save_img_from_vec("autovect" + to_string(i) + ".pgm", v[i]);
        }
    }
    fitMatrix = a.transpose();
    fitMatrix = v * fitMatrix; // Ya esta transpuesto la matrix de las alpha componentes principales
    fitMatrix = fitMatrix.transpose();
}

Matrix PCA::calculateRelatedMatrix(Matrix &matrix) {
    x = Matrix(matrix.n, matrix.m);
    median = calulateMedian(matrix);
    for (int i = 0; i < matrix.n; ++i) {
        x[i] = matrix[i] - median;
    }

    x = 1 / sqrt(matrix.n - 1) * x;

    Matrix transposed = x.transpose();
    Matrix covMatrix = x * transposed;
    return covMatrix;
}

//Transformacion Caracteristica de una muestra x
vector<double> PCA::tc(vector<double> &y) {
    return v * y;
}

