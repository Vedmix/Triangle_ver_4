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
    CmplxNum num(4, 1);
    CmplxNum num2(Fraction(4, 0), Fraction(2, 1));
    Fraction frc(-5, 1);
    frc.printFraction(); cout << '\n';
    return 0;
}
