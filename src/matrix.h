#include <utility>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Matrix {
public:
    Matrix(int n, int m);

    Matrix(int n);

    double getElem(int i, int j) const;

    void setElem(int i, int j, double val);

    pair<int, int> dimensions() const;

    friend Matrix operator*(const Matrix &m1, const Matrix &m2);

    friend Matrix operator*(double p, const Matrix &m);


private:
    int n, m;
    unordered_map<int, unordered_map<int, double> > matrix;
};

Matrix operator*(const Matrix &m1, const Matrix &m2);

Matrix operator+(const Matrix &a, const Matrix &b);

Matrix operator-(const Matrix &a, const Matrix &b);

Matrix operator*(double p, const Matrix &m);

vector<double> operator*(const Matrix &a, const vector<double> &x);

ostream &operator<<(ostream &os, const Matrix &matrix);

Matrix identity(int n);

double operator*(vector<double> const &x, vector<double> const &y);

double euclidianNorm(vector<double> &x);

void normalize(vector<double> &y);

double powerIteration(Matrix &a, int maxIterations, vector<double> &y);