#pragma once
#include "fraction.h"

class Vectors
{
private:
    Fraction* vec;
    int len;
public:
    Vectors(int ln,Fraction* vcInp);
    Vectors(int ln);
    Vectors(const std::string& filename);
    ~Vectors();
    void inputVector(Fraction* vcInp);
    int getLen();
    int getLen() const;
    Fraction& operator()(int n);
    const Fraction& operator()(int n) const;
    Vectors operator+(const Vectors& vec1) const;
    Vectors operator-(const Vectors& vec1) const;
    Vectors operator*(const Vectors& vec1) const;
    Vectors& operator=(const Vectors& other);
    void printVectorDecimal();
    void printVectorSimple();
};