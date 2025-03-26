#pragma once

class Matrix
{
    protected:
        double** mtx;
        int cols;
        int rows;
        double coeff; //обратный коэффициент матрицы (1/k) 
    public:
        Matrix(int rows, int cols);
        Matrix(const std::string& filename);
        ~Matrix();
        double determinant();
        double& operator()(int row, int col);
        const double& operator()(int row, int col) const;
        Matrix operator+(const Matrix& mtx1) const;
        Matrix operator-(const Matrix& mtx1) const;
        Matrix operator*(const Matrix& mtx1) const;
        Matrix& operator=(const Matrix& other);
        Matrix transpose();
        Matrix operator/(double scalar) const;
        void setCoeff(double cff);
        void devideMatrix(double cff) const;
        void inputMatrix(double** matrix);
        void printMartix();
        //void printMartixDecimal();
        //void printMatrixSimple();
        int getRows();
        int getCols();
        Matrix* inverseMatrix();
        double getElement(int n, int m);
        void setElement(int i, int j, int n);
};