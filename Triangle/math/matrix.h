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
        Fraction determinantRecursion();
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
        void multiplyString(int n, Fraction cff);
        Fraction getElement(int n, int m);
        Matrix* triangleMatrix();
        bool isNullVector(Fraction* vect);
        Fraction* getString(int n);
        void setString(Fraction* vec, int n);
        void removeNullStrings();
        int getRank();
        void swapRows(int row1, int row2);
        void subtractionString(int strNum1, int strNum2, Fraction cff); //вычитаем из строки под номером strNum1 строку номер strNum2
};