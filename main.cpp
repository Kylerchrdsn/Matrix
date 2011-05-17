#include "Matrix.h"
#include <iostream>

using namespace std;

int main()
{
    Matrix<double> A(2, 2),
                B(3, 4),
                C;

    double det;

    A[0][0] = 4; A[0][1] = 1;
    A[1][0] = 3; A[1][1] = 2;


    det = A.det();

    A.inverse();
    A.display();

    return 0;
}
