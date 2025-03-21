#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include <cmath>
using namespace std;

int main()
{
    Matrix syst("input.txt");
    double det = syst.determinant();
    cout << det;
    return 0;
}
