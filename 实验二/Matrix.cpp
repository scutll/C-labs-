#include "Matrix.h"

Matrix::Matrix(double a, double b, double c, double d){
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

Matrix::Matrix(Matrix &m){
    this->a = m.a;
    this->b = m.b;
    this->c = m.c;
    this->d = m.d;
}

Matrix Matrix::operator*(const Matrix &m2){
    return Matrix(this->a * m2.a + this->b * m2.c, this->a * m2.b + this->b * m2.d, this->c * m2.a + this->d * m2.c, this->c * m2.b + this->d * m2.d);
}

Matrix Matrix::operator*(const int i){
    return Matrix(i * this->a, i * this->b, i * this->c, i * this->d);
}

Matrix Matrix::operator+(const Matrix& m2){
    return Matrix(this->a + m2.a, this->b + m2.b, this->c + m2.c, this->d + m2.d);
}

Matrix Matrix::operator-(const Matrix&m2){
    return Matrix(this->a - m2.a, this->b - m2.b, this->c - m2.c, this->d - m2.d);
}

Matrix& Matrix::operator+=(const Matrix& m2){
    this->a += m2.a;
    this->b += m2.b;
    this->c += m2.c;
    this->d += m2.d;
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m2){
    this->a -= m2.a;
    this->b -= m2.b;
    this->c -= m2.c;
    this->d -= m2.d;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m2){

    int tmpa = this->a * m2.a + this->b * m2.c;
    int tmpb = this->a * m2.b + this->b * m2.d;
    int tmpc = this->c * m2.a + this->d * m2.c;
    int tmpd = this->c * m2.b + this->d * m2.d;
    this->a = tmpa;
    this->b = tmpb;
    this->c = tmpc;
    this->d = tmpd;
    return *this;
}

bool Matrix::operator==(const Matrix &m2) const{
    if (this->a==m2.a&&this->b==m2.b&&this->c==m2.c&&this->d==m2.d)
        return true;
    return false;
}

bool Matrix::operator!=(const Matrix&m2) const{
    return !(*this == m2);
}

std::ostream &operator<<(std::ostream &os, const Matrix &m){
    os << m.a << ' ' << m.b << std::endl
       << m.c << ' ' << m.d << std::endl;
    return os;
} 

std::istream& operator>>(std::istream& is,Matrix &m){
    is >> m.a >> m.b >> m.c >> m.d;
    return is;
}



