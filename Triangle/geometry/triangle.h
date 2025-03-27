#pragma once
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int existError();

class Triangle {
private:
    double ax, ay;
    double bx, by;
    double cx, cy;
    
    vector <double> lengthSidesTriangle();
    vector <double> anglesTriangle();
    vector <double> mediansTriangle();
public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
    void printInfo();

    vector<double> getSides();
    vector<double> getAngles();
    vector<double> getMedians();
};