#include <iostream>
#include "fraction.hpp"
#include "generalMathFunctions.hpp"
#include <cstring>
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

bool Fraction::operator>(const Fraction& frc){
    Fraction frc2 = frc;
    Fraction frc1 = *this;
    frc1.fractionReduction();
    frc2.fractionReduction();
    int lcm = foundLCM(frc1.down, frc2.down);
    frc1.down = lcm; frc2.down = lcm;
    frc1.up = frc1.up * (lcm/this->down); frc2.up = frc2.up * (lcm/frc.down);
    if(frc1.up>frc2.up){
        return true;
    }
    return false;
}

bool Fraction::operator<(const Fraction& frc){
    Fraction frc2 = frc;
    Fraction frc1 = *this;
    frc1.fractionReduction();
    frc2.fractionReduction();
    int lcm = foundLCM(frc1.down, frc2.down);
    frc1.down = lcm; frc2.down = lcm;
    frc1.up = frc1.up * (lcm/this->down); frc2.up = frc2.up * (lcm/frc.down);
    if(frc1.up<frc2.up){
        return true;
    }
    return false;
}

bool Fraction::operator>(const Fraction& frc)const{
    Fraction frc2 = frc;
    Fraction frc1 = *this;
    frc1.fractionReduction();
    frc2.fractionReduction();
    int lcm = foundLCM(frc1.down, frc2.down);
    frc1.down = lcm; frc2.down = lcm;
    frc1.up = frc1.up * (lcm/this->down); frc2.up = frc2.up * (lcm/frc.down);
    if(frc1.up>frc2.up){
        return true;
    }
    return false;
}

bool Fraction::operator<(const Fraction& frc)const{
    Fraction frc2 = frc;
    Fraction frc1 = *this;
    frc1.fractionReduction();
    frc2.fractionReduction();
    int lcm = foundLCM(frc1.down, frc2.down);
    frc1.down = lcm; frc2.down = lcm;
    frc1.up = frc1.up * (lcm/this->down); frc2.up = frc2.up * (lcm/frc.down);
    if(frc1.up<frc2.up){
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
    if(down<0){
        down*=-1;
        up*=-1;
    }
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

Fraction Fraction::absFr(){
    if(down<0){
        down*=-1;
        up*=-1;
    }
    Fraction res;
    if(up<0){
        res.setFraction(-up, down);
        return res;
    }
    res = *this;
    return res;
}

void Fraction::setFraction(int n1, int n2){up=n1;down=n2;}
int Fraction::getUp(){return up;}
int Fraction::getDown(){return down;}
int Fraction::getUp()const{return up;}
int Fraction::getDown()const{return down;}


Fraction atoFrc(const char* str){
    bool flag=false;
    int indexDown=0;
    int up, down=1;
    char* num = new char[12];
    for(int k=0; k<strlen(str);k++){
        if(str[k]=='/'){
            flag=true;
            indexDown=k+1;
            break;
        }
        num[k]=str[k];
        num[k+1]='\0';
    }
    up = stoi(num);
    if(flag){
        for(int k=indexDown; k<strlen(str);k++){
            num[k-indexDown] = str[k];
            num[k-indexDown+1]='\0';
        }
        down = stoi(num);
    }
    delete[] num;
    if(down<0){
        up*=-1;
        down*=-1;
    }
    return Fraction(up, down);
}

Fraction atoFrc(const string& str){
    bool flag=false;
    int indexDown=0;
    int up, down=1;
    char* num = new char[12];
    for(int k=0; k<str.length();k++){
        if(str[k]=='/'){
            flag=true;
            indexDown=k+1;
            break;
        }
        num[k]=str[k];
        num[k+1]='\0';
    }
    up = stoi(num);
    if(flag){
        for(int k=indexDown; k<str.length();k++){
            num[k-indexDown] = str[k];
            num[k-indexDown+1]='\0';
        }
        down = stoi(num);
    }
    delete[] num;
    if(down<0){
        up*=-1;
        down*=-1;
    }
    return Fraction(up, down);
}