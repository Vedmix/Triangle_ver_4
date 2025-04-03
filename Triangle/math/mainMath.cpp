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
    Matrix mtx("input.txt");
    mtx.printMatrixSimple();
    cout << '\n';
    mtx.triangleMatrix();
    mtx.printMatrixSimple();
    return 0;
}
