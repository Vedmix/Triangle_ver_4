#pragma once
class Fraction
{
private:
    int up;
    int down;
public:
    Fraction();
    Fraction(int n1, int n2);
    ~Fraction();
    Fraction operator+(const Fraction& frc) const;
    Fraction operator-(const Fraction& frc) const;
    Fraction operator*(const Fraction& frc) const;
    Fraction operator*(const int n1) const;
    Fraction operator/(const int n1) const;
    Fraction operator/(const Fraction& frc) const;
    Fraction& operator=(const Fraction& frc);
    bool operator==(const Fraction& frc);
    bool operator==(const Fraction& frc) const;
    void setFraction(int n1, int n2);
    void fractionReduction(); //Сокращение дроби
    void printFraction();
    int getUp();
    int getDown();
    int getUp() const;
    int getDown() const;
};
 