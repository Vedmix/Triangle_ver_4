#pragma once
#include <iostream>
#include <fstream>
#include "matrix.h"
#include <cmath>
using namespace std;


int** fileInput(const string& filename, int* n, int* m);

int SolveKramerMethod(int** syst, int n);