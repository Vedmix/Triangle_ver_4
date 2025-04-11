#pragma once
#include <vector>
#include <iostream>

class Tetragon {
private:
    double ax, ay, bx, by, cx, cy, dx, dy;
    double s, p;

    std::vector<double> calculateSides() const;
    std::vector<double> calculateAngles() const;
    std::vector<double> calculateDiagonals() const;
    std::vector<double> calculateSquare() const;
    std::vector<std::vector<double>> vectorTetra() const;

public:
    Tetragon(double x1, double y1, double x2, double y2,
             double x3, double y3, double x4, double y4);

    std::vector<double> getSides() const;
    std::vector<double> getAngles() const;
    std::vector<double> getDiagonals() const;
    std::vector<double> getSquare() const;
    std::vector<double> getPerimeter() const;
    std::vector<std::vector<double>> getVectors() const;
    std::vector<double> parallel() const;
};
