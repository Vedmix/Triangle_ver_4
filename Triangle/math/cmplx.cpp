#include <iostream>
#include "cmplx.hpp"
#include <cmath>

CmplxNum::CmplxNum(){
    re=Fraction(0, 1);
    im=Fraction(0, 1);
    mod=0;
    hasMod=true;
}

CmplxNum::CmplxNum(int real, int imag){
    re=Fraction(real, 1);
    im=Fraction(imag, 1);
    double reD = re.fracToDouble();
    double imD = im.fracToDouble();
    mod = sqrt(reD*reD + imD*imD);
    hasMod=true;
}

CmplxNum::CmplxNum(Fraction real, Fraction imag){
    re=real;
    im=imag;
    if(real.getDown()!=0 && imag.getDown()!=0){
        double reD = re.fracToDouble();
        double imD = im.fracToDouble();
        mod = sqrt(reD*reD + imD*imD);
        hasMod=true;
    }
    else{
        hasMod = false;
    }
}

CmplxNum::~CmplxNum(){}

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
    else{
        mod = NULL;
    }
    return *this;
}

CmplxNum CmplxNum::operator+(const CmplxNum& other){
    CmplxNum res(this->re+other.re, this->im + other.im);
    return res;
}

CmplxNum CmplxNum::operator-(const CmplxNum& other){
    CmplxNum res(this->re-other.re, this->im - other.im);
    return res;
}

CmplxNum CmplxNum::operator*(const CmplxNum& other){
    CmplxNum res(this->re*other.re - this->im*other.im, this->re*other.im+this->im*other.re);
    return res;
}