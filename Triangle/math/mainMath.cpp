#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include "generalMathFunctions.h"
#include "fraction.h"
#include <cmath>
using namespace std;

int main()
{
    Fraction frc1(4, 1), frc2(1, 12), res(0, 0);
    res = frc1*frc2;
    res.printFraction();
    return 0;
}
