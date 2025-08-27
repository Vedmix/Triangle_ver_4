#include <iostream>
#include "fraction.hpp"
#include "generalMathFunctions.hpp"
using namespace std;

Fraction::Fraction(int n1, int n2)
{
    up = n1;
    down = n2;
}

Fraction::Fraction()
{
    up = 0;
    down = 1;
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
        res.up = up - frc.up;
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
    if(res.up<0 && res.down<0){
        res.up = -res.up;
        res.down = -res.down;
    }
    else if(res.down<0){
        res.up = -res.up;
        res.down = -res.down;
    }
    res.fractionReduction();
    return res;
}

Fraction Fraction::operator*(const int n1) const{
    Fraction res(0, 0);
    res.up = up*n1;
    res.down = down;
    if(res.up<0 && res.down<0){
        res.up = -res.up;
        res.down = -res.down;
    }
    else if(res.down<0){
        res.up = -res.up;
        res.down = -res.down;
    }
    res.fractionReduction();
    return res;
}

Fraction Fraction::operator/(const int n1) const{
    Fraction res(0, 0);
    res.up = up;
    res.down = down*n1;
    if(res.up<0 && res.down<0){
        res.up = -res.up;
        res.down = -res.down;
    }
    else if(res.down<0){
        res.up = -res.up;
        res.down = -res.down;
    }
    res.fractionReduction();
    return res;
}

Fraction Fraction::operator/(const Fraction& frc) const{
    Fraction res(0, 0);
    res.up = up*frc.down;
    res.down = down*frc.up;
    if(res.up<0 && res.down<0){
        res.up = -res.up;
        res.down = -res.down;
    }
    else if(res.down<0){
        res.up = -res.up;
        res.down = -res.down;
    }
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

bool Fraction::operator==(const Fraction& frc){
    Fraction frc1 = frc;
    frc1.fractionReduction();
    this->fractionReduction();
    if(frc.getUp() == this->getUp() && frc.getDown() == this->getDown()){
        return true;
    }
    return false;
}

bool Fraction::operator==(const Fraction& frc)const{
    Fraction frc1 = frc;
    Fraction frc2 = *this;
    frc1.fractionReduction();
    frc2.fractionReduction();
    if(frc.getUp() == frc2.getUp() && frc.getDown() == frc2.getDown()){
        return true;
    }
    return false;
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
    if(up==0 || down ==1){
        cout << up;
    }
    else{
        cout << up << '/' << down;
    }
}

double Fraction::fracToDouble(){
    if(getDown()!=0){
        return getUp()/getDown();
    }
    cout << "Знаменатель 0!\n";
    return 0;
}

void Fraction::setFraction(int n1, int n2){up=n1;down=n2;}
int Fraction::getUp(){return up;}
int Fraction::getDown(){return down;}
int Fraction::getUp()const{return up;}
int Fraction::getDown()const{return down;}