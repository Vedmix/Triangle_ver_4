#include <iostream>
#include <fstream>
#include "matrix.h"
#include "SolveSyst.h"
#include <cmath>
using namespace std;

int** fileInput(const string& filename, int* n, int* m) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return nullptr;
    }

    file >> *n >> *m;

    int** syst = new int*[*n];
    for (int i = 0; i < *n; i++) {
        syst[i] = new int[*m];
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            file >> syst[i][j];
        }
    }

    file.close();
    return syst;
}

int SolveKramerMethod(int** syst, double* solves, int n){
    int** systForKram = new int*[n];
    double* dets = new double[n+1];
    bool success=1;
    for(int i=0;i<n;i++){
        systForKram[i] = new int[n];
    }

    for(int col=0; col<n+1;col++){
        for(int i=0;i<n;i++){
            for(int j=0; j<n;j++){
                if(!(col==j)){
                    systForKram[i][j]=syst[i][j];
                }
                else{
                    systForKram[i][j] = syst[i][n];
                }
            }
        }
        dets[col] = determinant(systForKram, n);
        if(dets[col]==0 && col==n){
            return 0;
            break;
        }
    }

    for(int i=0; i<n;i++){
        solves[i] = dets[i]/dets[n];
    }

    for (int i = 0; i < n; i++) {
        delete[] systForKram[i];
    }
    delete[] systForKram;

    return 1;
}

int main() {
    int countCols;
    int n = 0;
    int m = 0;
    int** syst = fileInput("input.txt", &n, &m);
    double* solves = new double[n];
    bool success;

    if (syst == nullptr) {
        cout << "Ошибка ввода" <<endl;
        return 1;
    }

    //Решаем методом Крамера
    if(m-1==n){
        success = SolveKramerMethod(syst, solves, n);
    }

    if(!success){
        cout<<"Уравнение имеет бесконечное количество решений, либо не имеет их"<< endl;
    }
    else{
        for(int i =0; i<n;i++){
            if(abs(solves[i]) < 1e-9){
                solves[i] = 0.0;
            }
            solves[i]=round(solves[i] * 10000) / 10000;
            cout << solves[i] <<' ';
        }
    }

    for (int i = 0; i < n; i++) {
        delete[] syst[i];
    }
    delete[] syst;

    return 0;
}