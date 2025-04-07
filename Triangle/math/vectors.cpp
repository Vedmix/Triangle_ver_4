#include <iostream>
#include <fstream>
#include "vectors.h"
#include "fraction.h"
#include <cmath>
#include <cstring>
#include "generalMathFunctions.h"
using namespace std;

Vectors::Vectors(int ln, Fraction* vcInp){
    len = ln;
    vec = new Fraction[len];
    for(int i=0; i<len;i++){
        vec[i] = vcInp[i];
    }
}

Vectors::~Vectors(){
    delete[] vec;
}