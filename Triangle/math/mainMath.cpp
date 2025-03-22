#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include <cmath>
using namespace std;

int main()
{
    int** inp1 = new int*[3];
    for (int i = 0; i < 3; i++) {
        inp1[i] = new int[3];
    }

    int** inp2 = new int*[3];
    for (int i = 0; i < 3; i++) {
        inp2[i] = new int[3];
    }
    int k=0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inp1[i][j] = k;
            inp2[i][j] = k;
            k++;
        }
    }
    Matrix mtx1(3, 3), mtx2(3, 3), mtx3(3, 3), mtx4(3, 3);
    mtx1.inputMatrix(inp1);
    mtx2.inputMatrix(inp2);
    //SystemOfEquations syst("input.txt");
    //syst.Solve();
    mtx3 = mtx1 * mtx2;
    mtx1.printMartix();
    cout<<'\n';
    mtx4 = mtx1.transpose();
    mtx4.printMartix();

    for (int i = 0; i < 3; i++) {
        delete[] inp1[i];
        delete[] inp2[i];
    }
    delete[] inp1;
    delete[] inp2;
    return 0;
}
