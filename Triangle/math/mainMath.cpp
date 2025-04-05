#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include "generalMathFunctions.h"
#include "fraction.h"
#include <cmath>
using namespace std;

int main()
{
    Matrix mtx("inputDet.txt");
    Matrix* res = new Matrix(mtx.getRows(), mtx.getCols());
    mtx.printMatrixSimple();
    cout << '\n';
    res = mtx.triangleMatrix();
    res->printMatrixSimple();
    cout << '\n';
    int rk=mtx.getRank();
    cout << rk <<endl;
    Fraction det = mtx.determinantRecursion();
    det.printFraction();cout<<'\n';
    return 0;
}
