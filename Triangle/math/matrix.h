#pragma once
#include "fraction.h"

class Matrix
{
    protected:
        Fraction** mtx;
        int cols;
        int rows;
        Fraction coeff;
    public:
        Matrix(int rows, int cols);
        Matrix(const std::string& filename);
        ~Matrix();
        Fraction determinant();
        Fraction& operator()(int row, int col);
        const Fraction& operator()(int row, int col) const;
        Matrix operator+(const Matrix& mtx1) const;
        Matrix operator-(const Matrix& mtx1) const;
        Matrix operator*(const Matrix& mtx1) const;
        Matrix& operator=(const Matrix& other);
        Matrix transpose();
        Matrix operator/(int scalar) const;
        void multiplyMatrix(Fraction cff) const;
        void inputMatrix(Fraction** matrix);
        void printMartixDecimal();
        void printMatrixSimple();
        int getRows();
        int getCols();
        Fraction getCoeff();
        void setCoeff(Fraction inpCoeff);
        Matrix* inverseMatrix();
        Fraction getElement(int n, int m);
        void triangleMatrix();
        void subtractionString(int strNum1, int strNum2, Fraction cff); //вычитаем из строки под номером strNum1 строку номер strNum2
};