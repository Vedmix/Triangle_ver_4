#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include <cmath>
using namespace std;

int main()
{
    Matrix matrica("input.txt");
    matrica.printMartix();
    cout<<'\n';
    Matrix* inverse = matrica.inverseMatrix();
    Matrix mtxRes(4, 4);
    double det = matrica.determinant();
    cout << "Определитель: " << det << endl;
    if (inverse) {
        cout << "Inverse matrix:" << endl;
        inverse->printMartix();
        cout<<'\n';
    } else {
        cout << "Ошибка: Невозможно вычислить обратную матрицу." << endl;
    }

    mtxRes = *inverse*matrica;
    mtxRes.printMartix();
    delete inverse;
    return 0;
}
