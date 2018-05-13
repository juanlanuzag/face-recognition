#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include <assert.h>

#include "helpers.h"
#include "knn.h"
#include "matrix.h"
#include "xval.h"
// void powerIterationTest();

#include <bits/stdc++.h>

using namespace std;

template<typename T> string vec2str(vector<T> v){
	string res = "(";
	for(unsigned int i = 1; i < v.size(); i++){
		res += to_string(v[i-1]);
		res += ", ";
	}
	res += to_string(v[v.size()-1]);
	res += ")";
	return res;
}

int testKNN(){
	Matrix A = Matrix(5, 2);
	A[0][0] = 2; A[0][1] = 2;
	A[1][0] = 2; A[1][1] = 3;
	A[2][0] = 5.2; A[2][1] = 4.5;
	A[3][0] = 8.12; A[3][1] = 2.05;
	A[4][0] = 3.5; A[4][1] = -0.32;

	vector<int> y = vector<int>(5, 0);
	y[2] = 1; y[3] = 2; y[4] = 3;

	KNN model = KNN(A, y, 2);

	for(int i = 0; i < A.dimensions().first; i++){
		cout << vec2str(A[i]) << ": " << model.predict(A[i]) << endl;
	}
	cout << "Score para el mismo data set: " << model.score(A,y) << endl;
	return 0;
}

void testXVal(){
	vector<int> y {1,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5};
	vector<string> A;

	XVal cv_1 = XVal(3, false, false);
	XVal cv_2 = XVal(3, true, false);
	XVal cv_3 = XVal(3, false, true);
	XVal cv_4 = XVal(3, true, true);

	cout << "TAGS: " << vec2str(y) << endl;

	cout << "XVal false false: ";
	for(auto v : cv_1.get_folds(A, y))
		cout << vec2str(v) << " ";
	cout << endl;

	cout << "XVal true false: ";
	for(auto v : cv_2.get_folds(A, y))
		cout << vec2str(v) << " ";
	cout << endl;

	cout << "XVal false true: ";
	for(auto v : cv_3.get_folds(A, y))
		cout << vec2str(v) << " ";
	cout << endl;

	cout << "XVal true true: ";
	for(auto v : cv_4.get_folds(A, y))
		cout << vec2str(v) << " ";
	cout << endl;

}

void pcaTest() {
    Matrix X(100, 100);
    for (int i = 0; i < 100; ++i) {
        X[i] = randomVector(100);
    }
    Matrix B = pca(X, 10);
    assert(B.m == 10);
    cout << B << endl;
}

int main(int argc, char *argv[]) {
    testKNN();
    testXVal();
    pcaTest();
    return 0;
}

// void powerIterationTest() {
//     Matrix a = Matrix(3, 3);
//     a[0][0] = 1;
//     a[0][1] = 2;
//     a[0][2] = 1;
//     a[1][0] = -4;
//     a[1][1] = 7;
//     a[1][2] = 1;
//     a[2][0] = -1;
//     a[2][1] = -2;
//     a[2][2] = -1;
//     vector<double> eigenvector(3);
//     eigenvector[1] = 1;
//     eigenvector[2] = 1;
//     eigenvector[3] = 1;
//     double eigenvalue = powerIteration(a, 100, eigenvector);
//     assert(abs(eigenvalue - 5) <= 1e-8);
// }
