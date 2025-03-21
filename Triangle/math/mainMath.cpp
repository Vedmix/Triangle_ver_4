#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include <cmath>
using namespace std;

int main()
{
    SystemOfEquations syst("input.txt");
    syst.Solve();
    return 0;
}
