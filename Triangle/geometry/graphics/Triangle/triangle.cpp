#include "triangle.h"
#include <cmath>
#include <vector>
#include <iostream>

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
    : ax(x1), ay(y1), bx(x2), by(y2), cx(x3), cy(y3) {
    if ((ax == bx && ay == by) || (ax == cx && ay == cy) || (cx == bx && cy == by)) {
        std::cout << "Ошибка: Точки треугольника совпадают!" << std::endl;
        exit(1);
    }
}

std::vector<double> Triangle::calculateSides() const {
    double side_ab = sqrt(pow(bx - ax, 2) + pow(by - ay, 2));
    double side_bc = sqrt(pow(cx - bx, 2) + pow(cy - by, 2));
    double side_ac = sqrt(pow(cx - ax, 2) + pow(cy - ay, 2));
    return {side_ab, side_bc, side_ac};
}

std::vector<double> Triangle::getSides() const {
    return calculateSides();
}

std::vector<double> Triangle::calculateAngles() const {
    auto sides = calculateSides();
    double a = sides[0], b = sides[1], c = sides[2];

    double angleA = acos((b*b + c*c - a*a) / (2*b*c)) * (180.0 / M_PI);
    double angleB = acos((a*a + c*c - b*b) / (2*a*c)) * (180.0 / M_PI);
    double angleC = 180 - angleA - angleB;

    return {angleA, angleB, angleC};
}

std::vector<double> Triangle::getAngles() const {
    return calculateAngles();
}

std::vector<double> Triangle::calculateMedians() const {
    auto sides = calculateSides();
    double a = sides[0], b = sides[1], c = sides[2];

    double ma = 0.5 * sqrt(2*b*b + 2*c*c - a*a);
    double mb = 0.5 * sqrt(2*a*a + 2*c*c - b*b);
    double mc = 0.5 * sqrt(2*a*a + 2*b*b - c*c);

    return {ma, mb, mc};
}

std::vector<double> Triangle::getMedians() const {
    return calculateMedians();
}

void Triangle::printInfo() const {
    auto sides = getSides();
    auto angles = getAngles();
    auto medians = getMedians();

    std::cout << "Стороны:\n"
              << "AB: " << sides[0] << "\n"
              << "BC: " << sides[1] << "\n"
              << "AC: " << sides[2] << "\n\n"
              << "Углы:\n"
              << "∠A: " << angles[0] << "°\n"
              << "∠B: " << angles[1] << "°\n"
              << "∠C: " << angles[2] << "°\n\n"
              << "Медианы:\n"
              << "ma: " << medians[0] << "\n"
              << "mb: " << medians[1] << "\n"
              << "mc: " << medians[2] << std::endl;
}
