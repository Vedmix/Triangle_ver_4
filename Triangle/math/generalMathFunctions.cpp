#include "generalMathFunctions.h"
#include <cmath>
#include "fraction.h"

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

Fraction* substructVectors(Fraction* vec1, Fraction* vec2, int n){
    Fraction* vecRes = new Fraction[n];
    for(int i=0;i<n;i++){
        vecRes[i] = vec1[i]-vec2[i];
    }
    return vecRes;
}

Fraction* multVectByNum(Fraction* vec, int n, Fraction cff){
    Fraction* vecRes = new Fraction[n];
    for(int i=0;i<n;i++){
        vecRes[i] = vec[i]*cff;
    }
    return vecRes;
}