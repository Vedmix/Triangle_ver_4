#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include "generalMathFunctions.h"
#include "fraction.h"
#include "vectors.h"
#include <cmath>
using namespace std;

int main()
{
    Vectors vec("inputVec.txt"), vec1("inputVec2.txt");
    Vectors** vecs = new Vectors*[2];  // Массив указателей
    // Инициализация каждого элемента с нужными аргументами
    vecs[0] = new Vectors(3, new Fraction[3]{Fraction(1, 1), Fraction(2, 1), Fraction(3, 1)});  // Пример с конструктором Vectors(int ln, Fraction* vcInp)
    vecs[1] = new Vectors(3, new Fraction[3]{Fraction(4, 1), Fraction(5, 1), Fraction(6, 1)});    // Другой пример vecs = new Vectors[2];
    Vectors* vecRes = new Vectors(3);
    vecRes = vectProd(vecs, 2);
    vecRes->printVectorSimple();
    return 0;
}
