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
std::vector<std::string> Triangle::typeOfTriangle() const {
    auto angles = calculateAngles();
    double a_angle = angles[0], b_angle = angles[1], c_angle = angles[2];

    auto sides = calculateSides();
    double ab = sides[0], bc = sides[1], ac = sides[2];

    if (((ab + bc) > ac) && ((ac + bc) > ab) && ((ab + ac) > bc)) {
        if ((ab == bc) && (bc == ac)) {
            return {"Равносторонний треугольник"};
        }
        else if ((a_angle == 90.0) || (b_angle == 90.0) || (c_angle == 90.0)) {
            if (((ab != bc) && (bc == ac)) || ((ab == bc) && (bc != ac)) || ((ab == ac) && (ac != bc))) {
                return {"Прямоугольный треугольник с двумя равными сторонами"};
            }
            else {
                return {"Прямоугольный треугольник"};
            }
        }
        else if ((a_angle < 90.0) && (b_angle < 90.0) && (c_angle < 90.0)) {
            if (((ab != bc) && (bc == ac)) || ((ab == bc) && (bc != ac)) || ((ab == ac) && (ac != bc))) {
                return {"Остроугольный треугольник с двумя равными сторонами"};
            }
            else {
                return {"Остроугольный треугольник"};
            }
        }
        else if ((a_angle > 90.0) || (b_angle > 90.0) || (c_angle > 90.0)) {
            if (((ab != bc) && (bc == ac)) || ((ab == bc) && (bc != ac)) || ((ab == ac) && (ac != bc))) {
                return {"Тупоугольный треугольник с двумя равными сторонами"};
            }
            else {
                return {"Тупоугольный треугольник"};
            }
        }
    }
    return {"Невалидный треугольник"};
}

std::vector<std::string> Triangle::getType() const {
    return typeOfTriangle();
}
