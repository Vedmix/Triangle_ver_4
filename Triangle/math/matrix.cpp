#include <iostream>
#include "matrix.h"
using namespace std;

double determinant(int** matrix, int n){
    double dtrm=0;
    int subcol;

    if(n==1){
        return matrix[0][0];
    }
    if(n==2){
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    int** submatrix = new int*[n-1];
    for(int i=0; i<n-1; i++){
        submatrix[i] = new int[n-1];
    }

    for(int col=0; col<n;col++){
        for(int i=1;i<n;i++){
            subcol=0;
            for(int j=0; j<n; j++){
                if(j==col){
                    continue;
                }
                submatrix[i-1][subcol]=matrix[i][j];
                subcol++;
            }
        }
        dtrm += (col % 2 == 0 ? 1 : -1) * matrix[0][col] * determinant(submatrix, n-1);
    }

    for(int i=0; i<n-1; i++){
        delete[] submatrix[i];
    }
    delete[] submatrix;

    return dtrm;
}