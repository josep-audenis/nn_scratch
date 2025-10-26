#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <random>
#include <cassert>

class Matrix {

    private:
        int rows, cols;
        std::vector<float> data;
    
    public:
        Matrix();
        Matrix(int r, int c);
        Matrix(const Matrix& other);

        float& operator()(int i, int j);
        const float& operator()(int i , int j) const;

        Matrix& operator=(const Matrix& other);
        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;
        Matrix operator*(const float k) const;                      // Scalar on the right of the Matrix
        friend Matrix operator*(const float k, const Matrix& M);    // Scalar on the left of the Matrix
        Matrix operator/(const Matrix& other) const;
        Matrix operator/(float scalar) const;


        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const float k);
        Matrix& operator/=(const float k);
        
        static Matrix random(int r, int c, float mean = 0.0f, float std = 1.0f);
        Matrix hadamard(const Matrix& other) const;
        Matrix transpose() const;
        Matrix maximum(float scalar) const;
        Matrix maximum(const Matrix& other) const;
        Matrix exp() const;

        Matrix sumRows() const;
        Matrix sumCols() const;
        Matrix maxRows() const;
        Matrix maxCols() const;

        int getRows() const;
        int getCols() const;
        
        
        friend std::ostream& operator<<(std::ostream& os, const Matrix& M);
};


#endif