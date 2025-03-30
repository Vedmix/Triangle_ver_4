#pragma once
#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include "fraction.h"
#include <cmath>
using namespace std;

class SystemOfEquations : public Matrix
{
private:
    Fraction* solves;
    bool success; //Имеет ли уравнение конечное количество корней
public:
    void SolveKramerMethod();
    Fraction* getSolves();
    void printSolvesSimple();
    void printSolvesDecimal();
    SystemOfEquations(int rows, int cols);
    void inputSystem(Fraction** input);
    SystemOfEquations(const string& filename);
    ~SystemOfEquations();
    bool isSuccess();
    void Solve();
};