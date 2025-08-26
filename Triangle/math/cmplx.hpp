#pragma once
#include "fraction.hpp"

class CmplxNum
{
private:
    Fraction re;
    Fraction im;
    double mod;
    bool hasMod;
public:
    CmplxNum();
    CmplxNum(Fraction real, Fraction imag);
    CmplxNum(int real, int imag);
    CmplxNum operator=(const CmplxNum& other);
    CmplxNum operator+(const CmplxNum& other);
    CmplxNum operator-(const CmplxNum& other);
    CmplxNum operator/(const CmplxNum& other);
    CmplxNum operator*(const CmplxNum& other);
    CmplxNum operator+(const int num);
    void print();
    double getMod();
    ~CmplxNum();
};