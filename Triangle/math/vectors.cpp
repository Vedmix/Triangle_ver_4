#include <iostream>
#include <fstream>
#include <sstream>
#include "vectors.hpp"
#include "fraction.hpp"
#include <cmath>
#include <cstring>
#include "generalMathFunctions.hpp"
using namespace std;

Vectors::Vectors(int ln, Fraction* vcInp){
    len = ln;
    vec = new Fraction[len];
    for(int i=0; i<len;i++){
        vec[i] = vcInp[i];
    }
    countMod();
}

Vectors::Vectors(int ln){
    len = ln;
    vec = new Fraction[len];
    Fraction defValue = Fraction(0, 1);
    for(int i=0; i<len;i++){
        vec[i] = defValue;
    }
    countMod();
}

Vectors::Vectors(const string& filename) {
    ifstream file(filename);
    char* token = new char[25];
    char* num = new char[12];
    bool flag = false;
    int indexDown = 0;
    int up, down = 1;
    
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        len = 0;
        vec = nullptr;
        return;
    }

    len = 0;
    string line;
    while(getline(file, line)) {
        if(line.empty()) continue;
        istringstream iss(line);
        string temp_token;
        while(iss >> temp_token) {
            len++;
        }
        break;
    }

    if (len == 0) {
        vec = nullptr;
        file.close();
        return;
    }

    vec = new Fraction[len];

    file.clear();
    file.seekg(0);

    int current_index = 0;
    while (file >> token && current_index < len) {
        flag = false;
        for(int k = 0; k < strlen(token); k++) {
            if(token[k] == '/') {
                flag = true;
                indexDown = k + 1;
                break;
            }
            num[k] = token[k];
            num[k + 1] = '\0';
        }
        
        up = stoi(num);
        
        if(flag) {
            for(int k = indexDown; k < strlen(token); k++) {
                num[k - indexDown] = token[k];
                num[k - indexDown + 1] = '\0';
            }
            down = stoi(num);
            flag = false;
        }
        
        vec[current_index++] = Fraction(up, down);
        down = 1;
    }

    delete[] token;
    delete[] num;
    file.close();
    countMod();
}

void Vectors::countMod(){
    double n=0.0;
    for(int i=0;i<len;i++){
        double value = static_cast<double>(vec[i].getUp()) / vec[i].getDown();
        n += (value * value);
    }
    mod = sqrt(n);
}

Vectors::~Vectors() {
    delete[] vec;
}

Fraction& Vectors::operator()(int n){
    return vec[n];
}

const Fraction& Vectors::operator()(int n) const
{
    return vec[n];
}

Vectors Vectors::operator+(const Vectors& vec1) const{
    if(this->getLen()!=vec1.getLen()){
        throw invalid_argument("Ошибка: не совпадают длины векторов!");
    }
    Vectors res(len);
    for(int i=0;i<this->getLen();i++){
        res.vec[i] = this->vec[i]+vec1.vec[i];
    }
    res.countMod();
    return res;
}

Vectors Vectors::operator-(const Vectors& vec1) const{
    if(this->getLen()!=vec1.getLen()){
        throw invalid_argument("Ошибка: не совпадают длины векторов!");
    }
    Vectors res(len);
    for(int i=0;i<this->getLen();i++){
        res.vec[i] = this->vec[i]-vec1.vec[i];
    }
    res.countMod();
    return res;
}

Fraction Vectors::operator*(const Vectors& vec1) const{
    if(vec1.getLen()!=this->getLen()){
        throw invalid_argument("Векторы разной длины!");
        return Fraction(0, 1);
    }
    Fraction res(0, 1);
    for(int i=0; i<vec1.getLen();i++){
        res = res + (vec1(i)*(*this)(i));
    }
    return res;
}

Vectors& Vectors::operator=(const Vectors& other){
    if (this == &other) {
        return *this;
    }

    delete[] vec;

    len = other.len;
    mod = other.mod;
    vec = new Fraction[len];
    for (int i=0; i<len; i++) {
        vec[i] = other.vec[i];
    }

    return *this;
}

Vectors& Vectors::operator*(const Fraction& scalar) const{
    Vectors* res = new Vectors(len);
    for(int i=0;i<len;i++){
        (*res)(i) = vec[i]*scalar;
    }
    res->countMod();
    return *res;
}

Vectors& Vectors::operator/(const Fraction& scalar) const{
    Vectors* res = new Vectors(len);
    for(int i=0;i<len;i++){
        (*res)(i) = vec[i]/scalar;
    }
    res->countMod();
    return *res;
}

Vectors& Vectors::operator*(const int scalar) const{
    Vectors* res = new Vectors(len);
    for(int i=0;i<len;i++){
        (*res)(i) = vec[i]*scalar;
    }
    res->countMod();
    return *res;
}

Vectors& Vectors::operator/(const int scalar) const{
    Vectors* res = new Vectors(len);
    for(int i=0;i<len;i++){
        (*res)(i) = vec[i]/scalar;
    }
    res->countMod();
    return *res;
}

bool Vectors::isOrthogonal(Vectors* other){
    if(((*this)*(*other)).getUp()==0){
        return true;
    }
    return false;
}

double Vectors::angle(Vectors* other){
    Fraction sc = ((*this)*(*other));
    double md = this->getMod() * other->getMod();
    double cos;
    if(md < 1e-7){
        cout << "Ошибка: произведение модулей равно нулю! (значение угла - 0)" << '\n';
        return 0.0;
    }
    cos = (static_cast<double>(sc.getUp()) / sc.getDown())/md;
    return acos(cos);
}

void Vectors::inputVector(Fraction* vcInp){
    for(int i=0;i<len;i++){
        vec[i]=vcInp[i];
    }
}

int Vectors::getLen(){return len;}
int Vectors::getLen()const{return len;}

double Vectors::getMod(){return mod;}
double Vectors::getMod()const{return mod;}

void Vectors::setMod(double module){mod = module;}

void Vectors::printVectorSimple(){
    for(int i=0; i<len;i++){
        vec[i].printFraction();
        cout << ' ';
    }
    cout << '\n';
}