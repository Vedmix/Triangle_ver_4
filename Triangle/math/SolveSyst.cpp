#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include "fraction.h"
#include <cmath>
using namespace std;

SystemOfEquations::SystemOfEquations(int rows, int cols) : Matrix(rows, cols){
    solves = new Fraction[rows];
}

SystemOfEquations::SystemOfEquations(const string& filename):Matrix(filename){
    solves = new Fraction[getRows()];
}

SystemOfEquations::~SystemOfEquations(){
    delete[] solves;
}

Fraction* SystemOfEquations::getSolves(){
    Fraction* copy = new Fraction[getRows()];
    for(int i = 0; i < getRows(); i++){
        copy[i] = solves[i];
    }
    return copy;
}

void SystemOfEquations::printSolvesSimple(){
    int rows = getRows();
    for(int i=0; i<rows;i++){
        cout << "x" << i+1 << " = ";
        solves[i].printFraction();
        cout << ' ';
    }
    cout << '\n';
}

void SystemOfEquations::inputSystem(Fraction** input){
    for(int i=0; i<rows;i++){
        for(int j=0; j<cols;j++){
            mtx[i][j] = input[i][j];
        }
    }
}

void SystemOfEquations::printSolvesDecimal(){
    int rows = getRows();
    double res;
    for(int i=0; i<rows;i++){
        res = solves->getUp()/solves->getDown();
        res=round(res * 10000) / 10000;
        cout << "x" << i+1 << " = " << res << ' ';
    }
    cout << '\n';
}

void SystemOfEquations::SolveKramerMethod(){
    int n = getRows();
    Matrix systForKram(n, n);
    Fraction* dets = new Fraction[n+1];

    for(int col=0; col<n+1;col++){
        for(int i=0;i<n;i++){
            for(int j=0; j<n;j++){
                if(col!=j){
                    systForKram(i, j) = (*this)(i, j);
                }
                else{
                    systForKram(i, j) = (*this)(i, n);
                }
            }
        }
        dets[col] = systForKram.determinant();
        if(dets[col].getUp()==0 && col==n){
            success=0;
            return;
        }
    }
    for(int i=0; i<n;i++){
        solves[i] = dets[i]/dets[n];
    }
}

void SystemOfEquations::SolveGaussMethod(){
    Fraction n;
    Matrix* syst = new Matrix(rows, cols);
    syst->inputMatrix(mtx);
    syst = syst->triangleMatrix();
    for(int i=syst->getRows()-1;i>0;i--){
        for(int j=i-1;j>-1;j--){
            n=(*syst)(j, i)/(*syst)(i, i);
            syst->subtractionString(j, i, n);
        }
    }
    if(syst->getCols()-1==syst->getRows()){
        for(int i=0;i<syst->getRows();i++){
            solves[i]=(*syst)(i, syst->getCols()-1);
        }
        success=true;
    }
    else{
        syst->printMatrixSimple();cout<<'\n';
        success=false;
    }
    
}

bool SystemOfEquations::isSuccess(){return success;}

void SystemOfEquations::Solve(){
    cout << "Введённая система: " << endl;
    printMatrixSimple();
    //Решаем методом Крамера
   
    if(isSuccess()){
        cout<<"Уравнение имеет бесконечное количество решений, либо не имеет их"<< endl;
    }
    else{
        cout << "Система решена" << endl;
    }
}