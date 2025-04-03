#include <iostream>
#include <fstream>
#include <sstream>
#include "matrix.h"
#include "fraction.h"
#include <cmath>
#include <cstring>
using namespace std;

Fraction& Matrix::operator()(int row, int col)
{
    return mtx[row][col];
}

const Fraction& Matrix::operator()(int row, int col) const
{
    return mtx[row][col];
}

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

    mtx = new Fraction*[rows];
    for(int i=0; i<rows; i++) {
        mtx[i] = new Fraction[cols];
    }

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            mtx[i][j] = other.mtx[i][j];
        }
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const{
    if (rows != other.rows || cols != other.cols) {
        throw invalid_argument("Ошибка: не совпадают размеры матриц!");
    }
    Matrix result(rows, cols);
    Matrix mtx1(rows, cols); mtx1 = *this;
    Matrix mtx2(rows, cols); mtx2 = other;
    if(coeff == other.coeff){
        result.coeff = coeff;
    }
    else{
        mtx1.multiplyMatrix(this->coeff);
        mtx2.multiplyMatrix(mtx2.coeff);
        result.coeff=Fraction(1, 1);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = mtx1(i, j) + mtx2(i, j);
        }
    }
    return result;
}

void Matrix::multiplyMatrix(Fraction cff) const{
    for(int i=0; i<rows;i++){
        for(int j=0; j<cols;j++){
            mtx[i][j] = mtx[i][j]*cff;
        }
    }
}


Matrix Matrix::operator-(const Matrix& other) const{
    if (rows != other.rows || cols != other.cols) {
        throw invalid_argument("Ошибка: не совпадают размеры матриц!");
    }
    Matrix result(rows, cols);
    Matrix mtx1(rows, cols); mtx1 = *this;
    Matrix mtx2(rows, cols); mtx2 = other;
    if(coeff == other.coeff){
        result.coeff = coeff;
    }
    else{
        mtx1.multiplyMatrix(this->coeff);
        mtx2.multiplyMatrix(mtx2.coeff);
        result.coeff=Fraction(1, 1);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = mtx1(i, j) - mtx2(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& mtx1) const{
    if (mtx1.cols != rows) {
        throw invalid_argument("Ошибка: не совпадает длина столбцов и длина строк!");
    }
    Matrix result(rows, mtx1.cols);
    Matrix mx1(rows, cols); mx1 = *this;
    Matrix mx2(rows, cols); mx2 = mtx1;
    mx1.multiplyMatrix(mx1.coeff); mx2.multiplyMatrix(mx2.coeff);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < mtx1.cols; j++) {
            for (int k = 0; k < cols; k++) {
                result(i, j) = result(i, j) + (mx1(i, k) * mx2(k, j));
            }
        }
    }

    return result;
}

Matrix Matrix::operator/(int scalar) const {
    if (abs(scalar) < 1e-9) {
        throw std::invalid_argument("Division by zero is not allowed");
    }

    Matrix result(rows, cols);
    Fraction frc(1, scalar);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = mtx[i][j] * frc;
        }
    }

    return result;
}

Matrix::Matrix(const string& filename){
    ifstream file(filename);
    char* token = new char[25];
    char* num = new char[12];
    bool flag = false;
    int indexDown=0;
    int up, down=1;
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return;
    }
    coeff=Fraction(1, 1);
    rows = 0;
    cols = 0;
    string line;
    while(getline(file, line)){
        if(line.empty()) continue;
        rows++;
        istringstream iss(line);
        string token;
        int current_cols = 0;
        while(iss >> token){
            current_cols++;
        }

        if(rows == 1){
            cols = current_cols;
        }
        else if(current_cols != cols){
            cerr << "Ошибка: несовместимое количество столбцов в строке " << rows << endl;
            file.close();
            return;
        }
    }
    file.clear();
    file.seekg(0);
    mtx = new Fraction*[rows];
    for (int i = 0; i < rows; i++)
    {
        mtx[i] = new Fraction[cols];
    }
    int inp;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file >> token;
            for(int k=0; k<strlen(token);k++){
                if(token[k]=='/'){
                    flag=true;
                    indexDown=k+1;
                    break;
                }
                num[k]=token[k];
                num[k+1]='\0';
            }
            up = stoi(num);
            if(flag){
                for(int k=indexDown; k<strlen(token);k++){
                    num[k-indexDown] = token[k];
                    num[k-indexDown+1]='\0';
                }
                down = stoi(num);
                flag=false;
            }
            mtx[i][j]=Fraction(up, down);
            down=1;
        }
    }
    file.close();
}

Matrix::Matrix(int rows, int cols){
    mtx = new Fraction*[rows];
    Fraction cff(1, 1);
    coeff=cff;
    for(int i=0; i<rows; i++)
    {
        mtx[i] = new Fraction[cols];
    }
    this->rows=rows;
    this->cols=cols;
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


Fraction Matrix::determinant(){
    if(rows!=cols){
        cout<<"Невозможно найти определитель неквадратной матрицы!"<<endl;
        return Fraction(0, 0);
    }
    if(coeff.getUp()!=1 || coeff.getDown()!=1){
        this->multiplyMatrix(coeff);
    }
    if(rows==1){
        return mtx[0][0];
    }
    if(rows==2){
        return mtx[0][0] * mtx[1][1] - mtx[0][1] * mtx[1][0];
    }
    Fraction dtrm(0, 1);
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

        Fraction subDet = submatrix.determinant();
        if(col%2==0){
            dtrm = dtrm + mtx[0][col]*subDet;
        }
        else{
            Fraction fr(-1, 1);
            dtrm = dtrm + fr*mtx[0][col]*subDet;
        }
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

void Matrix::inputMatrix(Fraction** matrix){
    for(int i=0; i<rows;i++){
        for(int j=0; j<cols;j++){
            mtx[i][j] = matrix[i][j];
        }
    }
}


void Matrix::printMartixDecimal(){
    if(coeff.getUp()!=1 || coeff.getDown() != 1){
        cout << "Коэффициент матрицы: "<<coeff.getUp() << '/' << coeff.getDown()<<endl;
    }
    double res;
    for(int i=0; i<rows;i++){
        for(int j=0;j<cols;j++){
            if(mtx[i][j].getDown()==0){
                cout << "Деление на ноль!" << endl;
                return;
            }
            res = mtx[i][j].getUp()/mtx[i][j].getDown();
            if(res < 1e-9){
                res = 0.0;
            }
            res=round(res * 100) / 100;
            cout << res << ' ';
        }
        cout << '\n';
    }
}

void Matrix::printMatrixSimple(){
    if(coeff.getUp()!=1 || coeff.getDown()!=1){
        cout << "Коэффициент матрицы: "<<coeff.getUp() << '/' << coeff.getDown()<<endl;
    }
    for(int i=0; i<rows;i++){
        for(int j=0; j<cols;j++){
            mtx[i][j].printFraction();
            cout << ' ';
        }
        cout << '\n';
    }
}



Matrix* Matrix::inverseMatrix() {
    if(rows != cols){
        cout << "Ошибка: Матрица должна быть квадратной!" << endl;
        return nullptr;
    }
    Fraction det = this->determinant();
    if(det.getUp()==0){
        cout << "Ошибка: Определитель матрицы равен нулю, обратной матрицы не существует!" << endl;
        return nullptr;
    }
    Matrix* result = new Matrix(rows, cols);
    result->coeff.setFraction(det.getDown(), det.getUp());
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
            Fraction minorDet = addMatrix.determinant();
            if((rws+cls)%2==0){
                (*result)(rws, cls) = minorDet;
            }
            else{
                (*result)(rws, cls) = minorDet * (-1);
            }
        }
    }
    *result=result->transpose();
    if(det.getUp()<0){
        for(int i=0; i<rows;i++){
            for(int j=0;j<cols;j++){
                (*result)(i, j) = (*result)(i, j) * (-1);
            }
        }
        result->coeff = result->coeff * (-1);
    }
    if(result->coeff.getDown()==1){
        for(int i=0; i<rows;i++){
            for(int j=0;j<cols;j++){
                (*result)(i, j) = (*result)(i, j) * result->coeff;
            }
        }
        result->coeff=Fraction(1, 1);
    }

    return result;
}

int Matrix::getCols(){return cols;}
int Matrix::getRows(){return rows;}

Fraction Matrix::getCoeff(){return coeff;}
void Matrix::setCoeff(Fraction inpCoeff){coeff = inpCoeff;}

void Matrix::subtractionString(int strNum1, int strNum2, Fraction cff){
    for(int i=0;i<cols;i++){
        mtx[strNum1][i] = mtx[strNum1][i] - cff*mtx[strNum2][i];
    }
}
void Matrix::triangleMatrix(){
    Fraction n;
    for(int i=1; i<rows;i++){
        for(int j=i;j<rows;j++){
            n = mtx[j][i-1]/mtx[i-1][i-1];
            this->subtractionString(j, i-1, n);
        }
    }
}