#include <iostream>
#include "fraction.h"
#include "generalMathFunctions.h"
using namespace std;

Fraction::Fraction(int n1, int n2)
{
    up = n1;
    down = n2;
}
 
Fraction::~Fraction()
{
}



Fraction Fraction::operator+(const Fraction& frc) const{
    Fraction res(0, 0);
    int lcm;//НОК
    if(down==frc.down){
        res.up = up + frc.up;
        res.down = down;
        res.fractionReduction();
        return res;
    }
    lcm = foundLCM(down, frc.down);
    res.up = up * (lcm/down) + frc.up * (lcm/frc.down);
    res.down=lcm;
    res.fractionReduction();
    return res;
}

Fraction Fraction::operator-(const Fraction& frc) const{
    Fraction res(0, 0);
    int lcm;//НОК
    if(down==frc.down){
        res.up = up + frc.up;
        res.down = down;
        res.fractionReduction();
        return res;
    }
    lcm = foundLCM(down, frc.down);
    res.up = up * (lcm/down) - frc.up * (lcm/frc.down);
    res.down=lcm;
    res.fractionReduction();
    return res;
}

Fraction Fraction::operator*(const Fraction& frc) const{
    Fraction res(0, 0);
    res.up = up*frc.up;
    res.down = down*frc.down;
    res.fractionReduction();
    return res;
}

Fraction Fraction::operator/(const Fraction& frc) const{
    Fraction res(0, 0);
    res.up = up*frc.down;
    res.down = down*frc.up;
    res.fractionReduction();
    return res;
}

Fraction& Fraction::operator=(const Fraction& frc){
    if(this == &frc){
        return *this;
    }
    up = frc.up;
    down = frc.down;
    return *this;
}

void Fraction::fractionReduction(){
    if(down==0){
        return;
    }
    int gcd = foundGCD(up, down); //НОД
    while(gcd!=1){
        up/=gcd;
        down/=gcd;
        gcd = foundGCD(up, down);
    }
}

void Fraction::printFraction(){
    cout << up << '/' << down << endl;
}