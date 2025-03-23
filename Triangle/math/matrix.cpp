#include <iostream>
#include <fstream>
#include "matrix.h"
#include <cmath>
using namespace std;

double& Matrix::operator()(int row, int col)
{
    return mtx[row][col];
}

const double& Matrix::operator()(int row, int col) const
{
    return mtx[row][col];
}
void Matrix::setElement(int i, int j, int n){mtx[i][j]=n;}
double Matrix::getElement(int n, int m){return mtx[n][m];}


Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }

    for(int i=0; i<rows;i++) {
         delete[] mtx[i];
    }
    delete[] mtx;

    rows = other.rows;
    cols = other.cols;
    coeff = other.coeff;

    mtx = new double*[rows];
    for(int i=0; i<rows; i++) {
        mtx[i] = new double[cols];
    }

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            mtx[i][j] = other.mtx[i][j];
        }
    }

    return *this;
}

void Matrix::setCoeff(double cff){coeff = cff;}

Matrix Matrix::operator+(const Matrix& other) const{
    if (rows != other.rows || cols != other.cols) {
        throw invalid_argument("Ошибка: не совпадают размеры матриц!");
    }
    Matrix result(rows, cols);
    Matrix temp(rows, cols);
    /*if(coeff!=other.coeff){
        this->devideMatrix(coeff);
        other.devideMatrix(coeff);
    }
    else{
        result.coeff=this->coeff;
    }*/
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = mtx[i][j] + other(i, j);
        }
    }
    return result;
}

void Matrix::devideMatrix(double cff) const{
    for(int i=0; i<rows;i++){
        for(int j=0; j<cols;j++){
            mtx[i][j] = mtx[i][j]/cff;
        }
    }
}


Matrix Matrix::operator-(const Matrix& mtx1) const{
    if (rows != mtx1.rows || cols != mtx1.cols) {
        throw invalid_argument("Ошибка: не совпадают размеры матриц!");
    }
    Matrix result(rows, cols);
    /*if(coeff!=mtx1.coeff){
        this->devideMatrix(coeff);
        mtx1.devideMatrix(coeff);
    }
    else{
        result.coeff=this->coeff;
    }*/
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = mtx[i][j] - mtx1(i, j);
        }
    }

    return result;
}

Matrix Matrix::operator*(const Matrix& mtx1) const{
    if (mtx1.cols != rows) {
        throw invalid_argument("Ошибка: не совпадает длина столбцов и длина строк!");
    }
    Matrix result(rows, mtx1.cols);
    /*if(coeff!=mtx1.coeff){
        this->devideMatrix(coeff);
        mtx1.devideMatrix(coeff);
    }
    else{
        result.coeff=this->coeff;
    }*/
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < mtx1.cols; j++) {
            for (int k = 0; k < cols; k++) {
                mtx[i][j]=mtx[i][j]/coeff;
                result(i, j) += mtx[i][k] * mtx1(k, j);
            }
        }
    }

    return result;
}

Matrix Matrix::operator/(double scalar) const {
    if (abs(scalar) < 1e-9) {
        throw std::invalid_argument("Division by zero is not allowed");
    }

    Matrix result(rows, cols);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = mtx[i][j] / scalar;
        }
    }

    return result;
}

Matrix::Matrix(const string& filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return;
    }
    coeff=1;
    file >> rows >> cols;
    mtx = new double*[rows];
    for (int i = 0; i < rows; i++)
    {
        mtx[i] = new double[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file >> mtx[i][j];
        }
    }

    file.close();
}

Matrix::Matrix(int rows, int cols){
    mtx = new double*[rows];
    coeff=1;
    for(int i=0; i<rows; i++)
    {
        mtx[i] = new double[cols];
    }
    this->rows=rows;
    this->cols=cols;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            mtx[i][j]=0;
        }
    }
}



Matrix::~Matrix() {
    if(mtx){
        for(int i=0; i<rows; i++){
            if(mtx[i]){
                delete[] mtx[i];
                mtx[i] = nullptr;
            }
        }
        delete[] mtx;
        mtx = nullptr;
    }
}


double Matrix::determinant(){
    if(rows!=cols){
        cout<<"Невозможно найти определитель неквадратной матрицы!"<<endl;
        return 0;
    }
    if(coeff!=1){
        this->devideMatrix(coeff);
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

Matrix Matrix::transpose(){
    Matrix result(cols, rows);
    result.coeff=this->coeff;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = mtx[j][i];
        }
    }

    return result;
}

void Matrix::inputMatrix(double** matrix){
    for(int i=0; i<rows;i++){
        for(int j=0; j<cols;j++){
            mtx[i][j] = matrix[i][j];
        }
    }
}

void Matrix::printMartix(){
    cout << "Коэффициент матрицы: 1/"<<coeff<<endl;
    for(int i=0; i<rows;i++){
        for(int j=0;j<cols;j++){
            if(abs(mtx[i][j]) < 1e-9){
                mtx[i][j] = 0.0;
            }
            mtx[i][j]=round(mtx[i][j] * 100) / 100;
            cout << mtx[i][j] << ' ';
        }
        cout << '\n';
    }
}

Matrix* Matrix::inverseMatrix() {
    if(rows != cols){
        cout << "Ошибка: Матрица должна быть квадратной!" << endl;
        return nullptr;
    }

    double det = this->determinant();
    if(abs(det)<1e-9){
        cout << "Ошибка: Определитель матрицы равен нулю, обратной матрицы не существует!" << endl;
        return nullptr;
    }
    
    Matrix* result = new Matrix(rows, cols);
    result->coeff=det;
    Matrix addMatrix(rows-1, cols-1);

    for(int rws=0;rws<rows;rws++){
        for(int cls=0; cls < cols; cls++){
            int iterRows=0;
            for(int i=0;i<rows;i++){
                if (i == rws) continue;
                int iterCols = 0;
                for(int j=0; j<cols;j++){
                    if (j == cls) continue;
                    addMatrix(iterRows, iterCols)=(*this)(i, j);
                    iterCols++;
                }
                iterRows++;
            }
            double minorDet = addMatrix.determinant();
            (*result)(rws, cls) = pow(-1, rws + cls) * minorDet;
        }
    }
    *result=result->transpose();

    return result;
}



int Matrix::getCols(){return cols;}
int Matrix::getRows(){return rows;}