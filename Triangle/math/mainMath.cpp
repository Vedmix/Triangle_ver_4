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
    Matrix mtx("input4.txt");
    Matrix* res = new Matrix(mtx.getRows(), mtx.getCols());
    SystemOfEquations syst("input4.txt");
    mtx.printMatrixSimple();
    cout << '\n';
    res = mtx.triangleMatrix();
    res->printMatrixSimple();
    cout << '\n';
    int rk=mtx.getRank();
    cout << rk <<endl;
    syst.SolveGaussMethod();
    if(syst.isSuccess()){
        syst.printSolvesSimple();
    }
    return 0;
}
