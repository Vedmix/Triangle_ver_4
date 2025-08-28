#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include "SolveSyst.hpp"
#include "generalMathFunctions.hpp"
#include "fraction.hpp"
#include "vectors.hpp"
#include "cmplx.hpp"
#include <cmath>
#include <string>
using namespace std;

int main()
{
    string num("12/34");
    Fraction frc = atoFrc(num);
    frc.printFraction(); cout << '\n';
    return 0;
}
