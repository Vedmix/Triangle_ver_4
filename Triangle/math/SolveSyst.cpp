#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include <cmath>
using namespace std;

SystemOfEquations::SystemOfEquations(int rows, int cols) : Matrix(rows, cols){
    solves = new double[rows];
}

SystemOfEquations::SystemOfEquations(const string& filename):Matrix(filename){
    solves = new double[getRows()];
}

SystemOfEquations::~SystemOfEquations(){
    delete[] solves;
}

double* SystemOfEquations::getSolves(){
    double* copy = new double[getRows()];
    for(int i = 0; i < getRows(); i++){
        copy[i] = solves[i];
    }
    return copy;
}

void SystemOfEquations::printSolves(){
    int rows = getRows();
    for(int i=0; i<rows;i++){
        if(abs(solves[i]) < 1e-9){
            solves[i] = 0.0;
        }
        solves[i]=round(solves[i] * 10000) / 10000;
        cout << "x" << i+1 << " = " << solves[i] << ' ';
    }
    cout << '\n';
}

void SystemOfEquations::SolveKramerMethod(){
    int n = getRows();
    Matrix systForKram(n, n);
    double* dets = new double[n+1];

    for (int i = 0; i < n + 1; i++) {
        dets[i] = 0.0;
    }

    for(int col=0; col<n+1;col++){
        for(int i=0;i<n;i++){
            for(int j=0; j<n;j++){
                if(col!=j){
                    systForKram.setElement(i, j, getElement(i, j));
                }
                else{
                    systForKram.setElement(i, j, getElement(i, n));
                }
            }
        }
        dets[col] = systForKram.determinant();
        if(abs(dets[col]) < 1e-9){
            dets[col] = 0.0;
        }
        if(dets[col]==0 && col==n){
            success=0;
            return;
        }
    }
    for(int i=0; i<n;i++){
        solves[i] = dets[i]/dets[n];
    }
}

bool SystemOfEquations::isSuccess(){return success;}

void SystemOfEquations::Solve(){
    cout << "Введённая система: " << endl;
    printMartix();
    //Решаем методом Крамера
    if(getCols()-1==getRows()){
        SolveKramerMethod();
    }
    else{
        //тут будет гаусс мб
        cout << '\n';
    }
    if(isSuccess()){
        cout<<"Уравнение имеет бесконечное количество решений, либо не имеет их"<< endl;
    }
    else{
        cout << "Система решена" << endl;
    }
}