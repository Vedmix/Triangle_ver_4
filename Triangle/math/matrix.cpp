#include <iostream>
#include <fstream>

#include "matrix.h"
using namespace std;

int& Matrix::operator()(int row, int col)
{
    return mtx[row][col];
}

const int& Matrix::operator()(int row, int col) const
{
    return mtx[row][col];
}
void Matrix::setElement(int i, int j, int n){mtx[i][j]=n;}
int Matrix::getElement(int n, int m){return mtx[n][m];}

Matrix::Matrix(const string& filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return;
    }

    file >> rows >> cols;

    mtx = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        mtx[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file >> mtx[i][j];
        }
    }

    file.close();
}

Matrix::Matrix(int rows, int cols){
    mtx = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        mtx[i] = new int[cols];
    }
    this->rows = rows;
    this->cols = cols;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mtx[i][j] = 0;
        }
    }
}

Matrix::~Matrix(){
    for (int i = 0; i < rows; i++)
    {
        delete[] mtx[i];
    }
    delete[] mtx;
}

double Matrix::determinant(){
    if(rows!=cols){
        cout<<"Невозможно найти определитель неквадратной матрицы!"<<endl;
        return 0;
    }
    if(rows==1){
        return mtx[0][0];
    }
    if(rows==2){
        return mtx[0][0] * mtx[1][1] - mtx[0][1] * mtx[1][0];
    }
    double dtrm=0;
    int subcol;
    Matrix submatrix(rows-1, cols-1);
    for(int col=0; col<rows;col++){
        for(int i=1;i<rows;i++){
            subcol=0;
            for(int j=0; j<rows; j++){
                if(j==col){
                    continue;
                }
                submatrix(i-1, subcol)=mtx[i][j];
                subcol++;
            }
        }

        double subDet = submatrix.determinant();
        dtrm += (col % 2 == 0 ? 1 : -1) * mtx[0][col] * subDet;
    }

    return dtrm;
}

void Matrix::inputMatrix(int** matrix){
    for(int i=0; i<rows;i++){
        for(int j=0; j<cols;j++){
            mtx[i][j] = matrix[i][j];
        }
    }
}

void Matrix::printMartix(){
    for(int i=0; i<rows;i++){
        for(int j=0;j<cols;j++){
            cout << mtx[i][j] << ' ';
        }
        cout << '\n';
    }
}

int Matrix::getCols(){return cols;}
int Matrix::getRows(){return rows;}