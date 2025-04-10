#pragma once
#include <vector>
#include <iostream>

class Triangle {
private:
    double ax, ay;
    double bx, by;
    double cx, cy;

    std::vector<double> calculateSides() const;
    std::vector<double> calculateAngles() const;
    std::vector<double> calculateMedians() const;
    std::vector<std::string> typeOfTriangle() const;

    std::vector<double> calculateSquare() const;


public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3);

    std::vector<double> getSides() const;
    std::vector<double> getAngles() const;
    std::vector<double> getMedians() const;
    std::vector<std::string> getType() const;

    std::vector<double> getSquare() const;


};
