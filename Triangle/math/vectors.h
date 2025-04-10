#pragma once
#include <string>
#include "fraction.h"

class Vectors
{
private:
    Fraction* vec;
    void countMod();
    double mod;
    int len;
public:
    Vectors(int ln,Fraction* vcInp);
    Vectors(int ln);
    Vectors(const std::string& filename);
    ~Vectors();
    void inputVector(Fraction* vcInp);
    int getLen();
    int getLen() const;
    double getMod();
    double getMod() const;
    void setMod(double module);
    Fraction& operator()(int n);
    const Fraction& operator()(int n) const;
    Vectors operator+(const Vectors& vec1) const;
    Vectors operator-(const Vectors& vec1) const;
    Fraction operator*(const Vectors& vec1) const;
    Vectors& operator=(const Vectors& other);
    Vectors& operator*(const Fraction& scalar) const;
    Vectors& operator/(const Fraction& scalar) const;
    Vectors& operator*(const int scalar) const;
    Vectors& operator/(const int scalar) const;
    bool isOrthogonal(Vectors* other);
    double angle(Vectors* other);
    void printVectorDecimal();
    void printVectorSimple();
};