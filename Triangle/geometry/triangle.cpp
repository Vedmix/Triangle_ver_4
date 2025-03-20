#include <iostream>
#include "triangle.h"
#include <cmath>
#include <vector>

using namespace std;
double ax, ay;
double bx, by;
double cx, cy;

int existError(){
    cout << "Triangle is not exist!" << endl;
    exit(0);
}

vector <double> Triangle::lengthSidesTriangle() {

    double side_ab = sqrt(pow((bx - ax), 2) + pow((by - ay), 2));
    double side_bc = sqrt(pow((cx - bx), 2) + pow((cy - by), 2));
    double side_ac = sqrt(pow((cx - ax), 2) + pow((cy - ay), 2));

    return { side_ab, side_bc, side_ac };
}

vector <double> Triangle::anglesTriangle() {
    vector<double> sides = lengthSidesTriangle();

    double angle_cab = acos((pow(sides[0], 2) + pow(sides[2], 2) - pow(sides[1], 2)) / (2 * sides[0] * sides[2])) * (180.0 / M_PI);
    double angle_abc = acos((pow(sides[0], 2) + pow(sides[1], 2) - pow(sides[2], 2)) / (2 * sides[0] * sides[1])) * (180.0 / M_PI);
    double angle_bca = acos((pow(sides[1], 2) + pow(sides[2], 2) - pow(sides[0], 2)) / (2 * sides[1] * sides[2])) * (180.0 / M_PI);

    return { angle_cab, angle_abc, angle_bca };
}

vector <double> Triangle::mediansTriangle() {
    vector<double> sides = lengthSidesTriangle();

    double median_aa1 = 0.5 * sqrt(2 * pow(sides[2], 2) + 2 * pow(sides[1], 2) - pow(sides[0], 2));
    double median_bb1 = 0.5 * sqrt(2 * pow(sides[0], 2) + 2 * pow(sides[1], 2) - pow(sides[2], 2));
    double median_cc1 = 0.5 * sqrt(2 * pow(sides[0], 2) + 2 * pow(sides[2], 2) - pow(sides[1], 2));

    return { median_aa1, median_bb1, median_cc1 };

}

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3) :
    ax(x1), ay(y1), bx(x2), by(y2), cx(x3), cy(y3) {
        if ((ax == bx & ay == by) | (ax == cx & ay == cy) | (cx == bx & cy == by)){
            existError();
        }
}

void Triangle::printInfo() {

    vector <double> sides = lengthSidesTriangle();
    vector <double> angles = anglesTriangle();
    vector <double> medians = mediansTriangle();

    cout << "AB: " << sides[0] << endl;
    cout << "BC: " << sides[1] << endl;
    cout << "AC: " << sides[2] << endl;

    cout << "CAB: " << angles[0] << endl;
    cout << "ABC: " << angles[1] << endl;
    cout << "BCA: " << angles[2] << endl;

    cout << "AA1: " << medians[0] << endl;
    cout << "BB1: " << medians[1] << endl;
    cout << "CC1: " << medians[2] << endl;
}