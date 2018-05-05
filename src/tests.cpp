#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <assert.h>
#include "helpers.h"
#include <cmath>


vector<double> random_vector(int i);

using namespace std;

void powerIterationTest() {
    Matrix a = Matrix(3, 3);
    a[0][0] = 1;
    a[0][1] = 2;
    a[0][2] = 1;
    a[1][0] = -4;
    a[1][1] = 7;
    a[1][2] = 1;
    a[2][0] = -1;
    a[2][1] = -2;
    a[2][2] = -1;
    cout << a << endl;
    vector<double> eigenvector = random_vector(3);
    double eigenvalue = powerIteration(a, 1000, eigenvector);
    assert(abs(eigenvalue - 5) <= 1e-8);
    vector<double> values = deflation(a);
    cout << values[0] << " " << values[1] << " " << values[3] << endl;
}


int main(int argc, char *argv[]) {
    powerIterationTest();
    return 0;
}


