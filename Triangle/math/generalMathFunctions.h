#pragma once
#include <cmath>
#include "fraction.h"
#include "vectors.h"

int foundGCD(int a, int b); //Поиск Наибольщего общего делителя
int foundLCM(int a, int b); //Поиск Наименьшего общего кратного
Fraction* substructVectors(Fraction* vec1, Fraction* vec2, int n);
Fraction* multVectByNum(Fraction* vec, int n, Fraction cff);
Vectors* vectProd(Vectors** vecs, int n);