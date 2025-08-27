#include <iostream>
#include "cmplx.hpp"
#include <cmath>

CmplxNum::CmplxNum(){
    re=Fraction(0, 1);
    im=Fraction(0, 1);
    countMod();
}

CmplxNum::CmplxNum(int real, int imag){
    re=Fraction(real, 1);
    im=Fraction(imag, 1);
    countMod();
}

CmplxNum::CmplxNum(Fraction real, Fraction imag){
    re=real;
    im=imag;
    countMod();
}

CmplxNum::~CmplxNum(){}

void CmplxNum::countMod(){
    if(re.getDown()!=0 && im.getDown()!=0){
        double reD = re.fracToDouble();
        double imD = im.fracToDouble();
        mod = sqrt(reD*reD + imD*imD);
        hasMod=true;
    }
    else{
        hasMod = false;
    }
}

CmplxNum CmplxNum::operator=(const CmplxNum& other){
    if(this==&other){
        return *this;
    }
    re = other.re;
    im = other.im;
    hasMod = other.hasMod;
    if(hasMod){
        mod = other.mod;
    }
    return *this;
}

CmplxNum CmplxNum::operator+(const CmplxNum& other){
    CmplxNum res(this->re+other.re, this->im + other.im);
    return res;
}

CmplxNum CmplxNum::operator+(const int num){
    CmplxNum res(this->re + Fraction(num, 1), this->im);
    return res;
}

CmplxNum CmplxNum::operator-(const CmplxNum& other){
    CmplxNum res(this->re-other.re, this->im - other.im);
    return res;
}

CmplxNum CmplxNum::operator*(const CmplxNum& other){
    Fraction a = this->re, b = this->im, c = other.re, d=other.im;
    CmplxNum res(a*c - b*d, a*d + b*c);
    return res;
}

CmplxNum CmplxNum::operator/(const CmplxNum& other){
    Fraction a = this->re, b = this->im, c = other.re, d=other.im;
    CmplxNum res((a*c + b*d)/(c*c + d*d), (b*c - a*d)/(c*c + d*d));
    return res;
}

void CmplxNum::print(){
    re.printFraction();
}