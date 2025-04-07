#pragma once
#include "fraction.h"

class Vectors
{
private:
    Fraction* vec;
    int len;
public:
    Vectors(int ln,Fraction* vcInp);
    Vectors(int ln);
    Vectors(const std::string& filename);
    void inputVector(Fraction* vcInp);
    int getLen();
    ~Vectors();
};