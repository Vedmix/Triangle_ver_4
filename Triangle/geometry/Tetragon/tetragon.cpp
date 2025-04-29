#include "tetragon.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>

Tetragon::Tetragon(double x1, double y1, double x2, double y2,
                   double x3, double y3, double x4, double y4)
    : ax(x1), ay(y1), bx(x2), by(y2), cx(x3), cy(y3), dx(x4), dy(y4) {

    if ((ax == bx && ay == by) || (ax == cx && ay == cy) || (ax == dx && ay == dy)) {
        std::cout << "Error: Quadrilateral points coincide!" << std::endl;
        exit(1);
    }
}

double Tetragon::getSquare() const {
    return 0.5 * fabs((ax*by + bx*cy + cx*dy + dx*ay) - (ay*bx + by*cx + cy*dx + dy*ax));
}

double Tetragon::getPerimeter() const {
    return sqrt(pow(bx-ax,2) + pow(by-ay,2)) +  sqrt(pow(cx-bx,2) + pow(cy-by,2)) + sqrt(pow(dx-cx,2) + pow(dy-cy,2)) + sqrt(pow(dx-ax,2) + pow(dy-ay,2));
}

std::vector<double> Tetragon::calculateSides() const {
    return {
        sqrt(pow(bx-ax,2) + pow(by-ay,2)),
        sqrt(pow(cx-bx,2) + pow(cy-by,2)),
        sqrt(pow(dx-cx,2) + pow(dy-cy,2)),
        sqrt(pow(dx-ax,2) + pow(dy-ay,2))};
}

std::vector<std::vector<double>> Tetragon::vectorTetra() const {
    return {
        {bx-ax, by-ay},
        {cx-bx, cy-by},
        {dx-cx, dy-cy},
        {dx-ax, dy-ay}
    };
}

std::vector<double> Tetragon::calculateAngles() const {
    auto vecs = vectorTetra();
    const auto& ab = vecs[0];
    const auto& bc = vecs[1];
    const auto& cd = vecs[2];
    const auto& da = vecs[3];

    auto dot = [](const std::vector<double>& a, const std::vector<double>& b) {
        return a[0]*b[0] + a[1]*b[1];
    };
    auto mag = [](const std::vector<double>& v) {
        return sqrt(v[0]*v[0] + v[1]*v[1]);
    };

    double angle_a = acos(dot(ab, da)/(mag(ab)*mag(da))) * (180.0/M_PI);
    double angle_b = acos(dot(bc, {-ab[0], -ab[1]})/(mag(bc)*mag(ab))) * (180.0/M_PI);
    double angle_c = acos(dot(cd, {-bc[0], -bc[1]})/(mag(cd)*mag(bc))) * (180.0/M_PI);
    double angle_d = acos(dot(da, {-cd[0], -cd[1]})/(mag(da)*mag(cd))) * (180.0/M_PI);

    return {angle_a, angle_b, angle_c, angle_d};
}

std::vector<double> Tetragon::calculateDiagonals() const {
    return {
        sqrt(pow(cx-ax,2) + pow(cy-ay,2)),
        sqrt(pow(dx-bx,2) + pow(dy-by,2))
    };
}

std::vector<std::string> Tetragon::typeOfTetragon() const{
    auto par = parallel();
    bool parallel_abcd = par[0];
    bool parallel_bcda = par[1];

    auto angles = calculateAngles();
    double a_angle = angles[0], b_angle = angles[1], c_angle = angles[2], d_angle = angles[3];

    auto sides = calculateSides();
    double ab = sides[0], bc = sides[1], cd = sides[2], da = sides[2];

    double cross_a = (bx - ax) * (dy - ay) - (by - ay) * (dx - ax);
    double cross_b = (cx - bx) * (ay - by) - (cy - by) * (ax - bx);
    double cross_c = (dx - cx) * (by - cy) - (dy - cy) * (bx - cx);
    double cross_d = (ax - dx) * (cy - dy) - (ay - dy) * (cx - dx);

    if (((cross_a > 0) && (cross_b > 0) && (cross_c > 0) && (cross_d > 0)) || ((cross_a < 0) && (cross_b < 0) && (cross_c < 0) && (cross_d < 0))){
            if (parallel_abcd && parallel_bcda) {
            if (ab == bc && ab == cd && ab == da) {
                if (a_angle == 90.0 && b_angle == 90.0 &&
                    c_angle == 90.0 && d_angle == 90.0) {
                    return {"выпуклый","квадрат"};
                }
                return {"ромб"};
            } else if (a_angle == 90.0 && b_angle == 90.0 &&
                    c_angle == 90.0 && d_angle == 90.0) {
                return {"выпуклый","прямоугольник"};
            }
            return {"параллелограмм"};
        } else if (parallel_abcd || parallel_bcda) {
            return {"выпуклый","трапеция"};
        }
        return {"выпуклый","произвольный четырехугольник"};
    }
    else {
        return {"вогнутый","произвольный четырехугольник"};
    }
}

std::vector<std::string> Tetragon::getType() const{
    return typeOfTetragon();
}
std::vector<bool> Tetragon::parallel() const {
    auto v = vectorTetra();
    const auto& ab = v[0];
    const auto& cd = v[2];
    const auto& bc = v[1];
    const auto& da = v[3];

    double abcd = ab[0]*cd[1] - ab[1]*cd[0];
    double bcda = bc[0]*da[1] - bc[1]*da[0];

    bool abcdBool = (abcd == 0.0);
    bool bcdaBool = (bcda == 0.0);

    return {abcdBool, bcdaBool};
}

std::vector<double> Tetragon::getSides() const {
    return calculateSides();
}

std::vector<double> Tetragon::getAngles() const {
    return calculateAngles();
}

std::vector<double> Tetragon::getDiagonals() const {
    return calculateDiagonals();
}

std::vector<std::vector<double>> Tetragon::getVectors() const {
    return vectorTetra();
}
