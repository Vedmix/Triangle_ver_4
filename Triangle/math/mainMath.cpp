#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include "SolveSyst.hpp"
#include "generalMathFunctions.hpp"
#include "fraction.hpp"
#include "vectors.hpp"
#include "cmplx.hpp"
#include <cmath>
using namespace std;

int main()
{
    CmplxNum num1(4, 1), num2(0, 0), num3(-3, -5), num4(-3, 5), num5(0, 4);
    num1.print(); cout << '\n';
    num2.print(); cout << '\n';
    num3.print(); cout << '\n';
    num4.print(); cout << '\n';
    if(Fraction(-5, 1)>Fraction(0, 1)){
        cout << "incorr";
    }
    return 0;
}
