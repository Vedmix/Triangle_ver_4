#pragma once
#include <vector>
#include <iostream>

class Tetragon {
private:
    double ax, ay, bx, by, cx, cy, dx, dy;

    std::vector<double> calculateSides() const;
    std::vector<double> calculateAngles() const;
    std::vector<double> calculateDiagonals() const;
    std::vector<double> calculateSquare() const;
    std::vector<std::vector<double>> vectorTetra() const;
    std::vector<std::string> typeOfTetragon() const;

public:
    Tetragon(double x1, double y1, double x2, double y2,
             double x3, double y3, double x4, double y4);

    std::vector<double> getSides() const;
    std::vector<double> getAngles() const;
    std::vector<double> getDiagonals() const;
    double getSquare() const;
    double getPerimeter() const;
    std::vector<std::vector<double>> getVectors() const;
    std::vector<std::string> getType() const;
    std::vector<bool> parallel() const;
};
