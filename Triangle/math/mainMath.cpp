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
    Vectors vec("inputVec.txt");
    vec.printVectorSimple();
    return 0;
}
