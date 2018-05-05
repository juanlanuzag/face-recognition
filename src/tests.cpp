#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <assert.h>
#include "matrix.h"
#include "knn.h"
#include <cmath>

// void powerIterationTest();

using namespace std;


int main(int argc, char *argv[]) {
    // powerIterationTest();
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
