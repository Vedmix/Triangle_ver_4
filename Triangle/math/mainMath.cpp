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
    /*Fraction frc1(1, -3), frc2(1, -2), res(0, 0);
    Fraction frcs2[3][3] = {
     {Fraction(1, 1), Fraction(1, 1), Fraction(3, 1)},
     {Fraction(4, 1), Fraction(3, 1), Fraction(6, 1)}, 
     {Fraction(7, 1), Fraction(8, 1), Fraction(9, 1)}
    };
    Fraction frcs3[3][3] = {
        {Fraction(1, 1), Fraction(0, 1), Fraction(0, 1)},
        {Fraction(0, 1), Fraction(1, 1), Fraction(0, 1)}, 
        {Fraction(0, 1), Fraction(0, 1), Fraction(1, 1)}
       };
    Fraction frcsKr[4][4] = {
    {Fraction(1, 1), Fraction(1, 1), Fraction(1, 1), Fraction(1, 1)},
    {Fraction(1, 1), Fraction(-1, 1), Fraction(1, 1), Fraction(2, 1)}, 
    {Fraction(1, 1), Fraction(1, 1), Fraction(-1, 1), Fraction(3, 1)}
    };
    Matrix mtx(3, 3), mtxRes(3, 3), mtx2(3, 3);
    SystemOfEquations mtxSyst(3, 4);
    Fraction** frcInp = new Fraction*[3];
    for(int i=0; i<3; i++){
        frcInp[i] = new Fraction[4];
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            frcInp[i][j]=frcsKr[i][j];
        }
    }
    mtxSyst.inputMatrix(frcInp);
    mtxSyst.Solve();
    mtxSyst.printSolvesSimple();
    for(int i=0; i<3; i++){
        frcInp[i] = new Fraction[3];
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            frcInp[i][j]=frcs2[i][j];
        }
    }
    mtx.inputMatrix(frcInp);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            frcInp[i][j]=frcs3[i][j];
        }
    }
    mtx2.inputMatrix(frcInp);
    Fraction det = mtx.determinant();
    Matrix* inverse = mtx.inverseMatrix();
    if(inverse){
        cout << "Inverse matrix:" << endl;
        inverse->printMatrixSimple();
        res = inverse->getCoeff();
    }
    cout<<'\n';
    mtx.printMatrixSimple();
    cout << '\n';
    mtxRes = mtx*(*inverse);
    mtxRes.printMatrixSimple();*/
>>>>>>> daunito228
    return 0;
}
