#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include "generalMathFunctions.h"
#include "fraction.h"
#include "vectors.h";
#include <cmath>
using namespace std;

int main()
{
    Matrix Cge("inp1.txt"), Cgf("inp2.txt"), xe(1, 3), x("inpX.txt");
    Matrix* Ceg = new Matrix(3, 3);
    Matrix* Cef = new Matrix(3, 3);
    Matrix* Cfe = new Matrix(3, 3);
    Ceg = Cge.inverseMatrix();
    cout << "C(e->g): " << endl;
    Ceg->printMatrixSimple();
    *Cef = (*Ceg)*Cgf;
    cout << '\n';
    cout << "C(e->f):" << endl;
    Cef->printMatrixSimple();
    cout << '\n';
    cout << "C(f->e):" << endl;
    Cfe = Cef->inverseMatrix();
    Cfe->printMatrixSimple();
    xe = (*Ceg)*x;
    cout << "xe: " << endl;
    xe.printMatrixSimple();
    return 0;
}
