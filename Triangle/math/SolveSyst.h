#pragma once
#include <iostream>
#include <fstream>
#include "matrix.h"
#include <cmath>
using namespace std;

class SystemOfEquations : public Matrix
{
private:
    double* solves;
    bool success; //Имеет ли уравнение конечное количество корней
public:
    void SolveKramerMethod();
    double* getSolves();
    void printSolves();
    SystemOfEquations(int rows, int cols);
    SystemOfEquations(const string& filename);
    ~SystemOfEquations();
    bool isSuccess();
    void Solve();
};