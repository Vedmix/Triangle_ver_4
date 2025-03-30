#include "generalMathFunctions.h"
#include <cmath>

int foundGCD(int a, int b){
    a=abs(a);
    b=abs(b);
    int temp;
    if(a<b){
        temp=a;
        a=b;
        b=temp;
    }
    while(b!=0){
        a%=b;
        temp=a;
        a=b;
        b=temp;
    }
    return a;
}

int foundLCM(int a, int b){
    a=abs(a);
    b=abs(b);
    return (a*b)/foundGCD(a, b);
}