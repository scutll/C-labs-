#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
class Matrix{

public:
    Matrix(double a, double b, double c, double d);
    Matrix():a(0),b(0),c(0),d(0) {};
    Matrix(Matrix &m);
    Matrix operator+(const Matrix &m2);
    Matrix operator*(const Matrix &m2);
    Matrix operator*(const int i);
    Matrix operator-(const Matrix &m2);
    Matrix &operator+=(const Matrix& m2);
    Matrix &operator-=(const Matrix &m2);
    Matrix &operator*=(const Matrix &m2);
    bool operator==(const Matrix &m2) const;
    bool operator!=(const Matrix &m2) const;
    
    //输出插入符
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);
    //输入
    friend std::istream &operator>>(std::istream &is, Matrix &m);

private:
    int a, b, c, d;
};

#endif