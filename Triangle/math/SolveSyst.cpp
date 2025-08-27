#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include <sstream>
#include "SolveSyst.hpp"
#include <cstring>
#include "fraction.hpp"
#include <cmath>
using namespace std;

SystemOfEquations::SystemOfEquations(int rows, int cols) : Matrix(rows, cols){
    solves = new Fraction[rows];
    hasParam=false;
}

SystemOfEquations::SystemOfEquations(const string& filename):Matrix(filename){
    solves = new Fraction[getRows()];
    hasParam=false;
}

SystemOfEquations::~SystemOfEquations(){
    delete[] solves;
    if(hasParam && solvesWithParam){
        for(int i = 0; i < this->getRows(); i++){
            if(solvesWithParam[i]){
                delete[] solvesWithParam[i];
            }
        }
        delete[] solvesWithParam;
    }
}

Fraction* SystemOfEquations::getSolves(){
    Fraction* copy = new Fraction[getRows()];
    for(int i = 0; i < getRows(); i++){
        copy[i] = solves[i];
    }
    return copy;
}

void SystemOfEquations::printSolvesSimple() {
    if(!success){
        std::cout << "Система не имеет решений!" << std::endl;
        return;
    }

    if(hasParam){
        std::cout << "Система имеет бесконечное множество решений:" << std::endl;
        
        int numBasicVars = getRows();
        int numParams = getCols() - numBasicVars - 1;

        for(int i = 0; i < numBasicVars; i++){
            std::cout << "x" << i+1 << " = " << solvesWithParam[i] << std::endl;
        }

        for(int i = 0; i < numParams; i++){
            std::cout << "x" << numBasicVars + i + 1 << " = t" << i+1 << std::endl;
        }
    }
    else{
        std::cout << "Система имеет единственное решение:" << std::endl;
        for(int i = 0; i < getRows(); i++){
            std::cout << "x" << i+1 << " = ";
            solves[i].printFraction();
            std::cout << std::endl;
        }
    }
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
    int solvesWithParamSize;
    Matrix* syst = new Matrix(rows, cols);
    syst->inputMatrix(mtx);
    syst = syst->triangleMatrix();
    for(int i=syst->getRows()-1;i>-1;i--){
        if(syst->isUnsolveString(i)){
            success=false;
            return;
        }
    }
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
    }
    else{
        hasParam = true;
        int numBasicVars = syst->getRows();
        int numParams = syst->getCols() - numBasicVars - 1;
        int totalVars = numBasicVars + numParams;
        solvesWithParamSize = totalVars;
        solvesWithParam = new char*[totalVars];
        
        for(int i=0; i<numBasicVars; i++){
            std::stringstream ss;
            Fraction freeTerm = (*syst)(i, syst->getCols()-1) / (*syst)(i,i);
            
            if(freeTerm.getUp() != 0){
                ss << freeTerm.getUp();
                if(freeTerm.getDown() != 1) ss << "/" << freeTerm.getDown();
            } 
            else{
                ss << "0";
            }
            
            for(int p=0; p<numParams; p++) {
                Fraction coeff = (*syst)(i, syst->getRows()+p) / (*syst)(i,i);
                if(coeff.getUp()!=0){
                    ss << (coeff.getUp()>0 ? " - " : " + ");
                    if(abs(coeff.getUp())!=1 || coeff.getDown()!=1){
                        ss << abs(coeff.getUp());
                        if(coeff.getDown()!=1){
                            ss << "/" << coeff.getDown();
                        }
                        ss << "*";
                    }
                    ss << "t" << p+1;
                }
            }
            
            std::string solution = ss.str();
            solvesWithParam[i] = new char[solution.length() + 1];
            strcpy(solvesWithParam[i], solution.c_str());
        }

        for(int p=0; p < numParams; p++){
            std::string param = "t" + std::to_string(p+1);
            solvesWithParam[numBasicVars + p] = new char[param.length() + 1];
            strcpy(solvesWithParam[numBasicVars + p], param.c_str());
        }
    }
    delete syst;
    success=true;
}

void SystemOfEquations::inputSystemFromFile(const string& filename){

}

bool SystemOfEquations::isSuccess(){return success;}

void SystemOfEquations::Solve(){
    cout << "Введённая система: " << endl;
    printMatrixSimple();
    SolveGaussMethod();
    if(!success){
        cout << "Система не имеет решений!"<<endl;
    }
    else{
        cout << "Система решена" << endl;
    }
}