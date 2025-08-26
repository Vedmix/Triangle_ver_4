#include "generalMathFunctions.hpp"
#include <cmath>
#include <iostream>
#include "matrix.hpp"
#include "fraction.hpp"
using namespace std;

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

Vectors* vectProd(Vectors** vecs, int n){
    if((*vecs)[0].getLen()-1 != n){
        throw invalid_argument("Не найти векторное произведение");
        return nullptr;
    }

    Matrix mtxDet(n, n);
    Vectors* res = new Vectors(n+1);
    int mtxCols=0;
    for(int i=0;i<n+1;i++){
        for(int j=0; j<n;j++){
            mtxCols=0;
            for(int k=0;k<n+1;k++){
                if(i!=k){
                    mtxDet(j, mtxCols) = (*vecs[j])(k);
                    mtxCols++;
                }
            }
        }
        if((i+1)%2==0){
            (*res)(i) = (mtxDet.determinant())*(-1);
        }
        else{
            (*res)(i) = mtxDet.determinant();
        }
    }
    double m=0.0;
    for(int i=0;i<res->getLen();i++){
        double value = static_cast<double>((*res)(i).getUp()) / (*res)(i).getDown();
        m += (value * value);
    }
    res->setMod(sqrt(m));
    return res;
}

Fraction* multVectByNum(Fraction* vec, int n, Fraction cff){
    Fraction* vecRes = new Fraction[n];
    for(int i=0;i<n;i++){
        vecRes[i] = vec[i]*cff;
    }
    return vecRes;
}