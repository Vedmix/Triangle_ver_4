#pragma once
#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include "SolveSyst.hpp"
#include "fraction.hpp"
#include <cmath>
using namespace std;

class SystemOfEquations : public Matrix
{
private:
    Fraction* solves;
    char** solvesWithParam;
    bool success;
    bool hasParam; //Имеет ли уравнение конечное количество корней
public:
    void SolveGaussMethod();
    void SolveKramerMethod();
    Fraction* getSolves();
    void printSolvesSimple();
    void printSolvesDecimal();
    SystemOfEquations(int rows, int cols);
    void inputSystem(Fraction** input);
    SystemOfEquations(const string& filename);
    ~SystemOfEquations();
    void inputSystemFromFile(const string& filename);
    bool isSuccess();
    void Solve();
};