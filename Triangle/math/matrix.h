#pragma once

struct Fraction
{
    int up;
    int down;
};

class Matrix
{
    protected:
        int** mtx;
        int cols;
        int rows;
    public:
        Matrix(int rows, int cols);
        Matrix(const std::string& filename);
        ~Matrix();
        double determinant();
        int& operator()(int row, int col);
        const int& operator()(int row, int col) const;
        void inputMatrix(int** matrix);
        void printMartix();
        int getRows();
        int getCols();
        int getElement(int n, int m);
        void setElement(int i, int j, int n);
};