#pragma once
class Fraction
{
private:
    int up;
    int down;
public:
    Fraction(int n1, int n2);
    ~Fraction();
    Fraction operator+(const Fraction& frc) const;
    Fraction operator-(const Fraction& frc) const;
    Fraction operator*(const Fraction& frc) const;
    Fraction operator/(const Fraction& frc) const;
    Fraction& operator=(const Fraction& frc);
    void fractionReduction(); //Сокращение дроби
    void printFraction();
};
 