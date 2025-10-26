#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <random>
#include <numeric>
#include <cstdint>
#include <cassert>

class Matrix {

    private:
        int rows_, cols_;
        std::vector<double> data_;
    
    public:
        Matrix();
        Matrix(int r, int c);
        Matrix(const Matrix& other);

        double& operator()(int i, int j);
        const double& operator()(int i , int j) const;

        Matrix& operator=(const Matrix& other);
        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;
        Matrix operator*(const double k) const;                      // Scalar on the right of the Matrix
        friend Matrix operator*(const double k, const Matrix& M);    // Scalar on the left of the Matrix
        Matrix operator/(const Matrix& other) const;
        Matrix operator/(double scalar) const;


        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const double k);
        Matrix& operator/=(const double k);
        
        static Matrix random(int r, int c, double mean = 0.0f, double std = 1.0f);
        Matrix hadamard(const Matrix& other) const;
        Matrix transpose() const;
        Matrix maximum(double scalar) const;
        Matrix maximum(const Matrix& other) const;
        Matrix exp() const;
        Matrix clipped(double min_val, double max_val) const;

        Matrix sumRows() const;
        Matrix sumCols() const;
        Matrix maxRows() const;
        Matrix maxCols() const;

        int getSize() const;
        int getRows() const;
        int getCols() const;
        
        
        friend std::ostream& operator<<(std::ostream& os, const Matrix& M);
};


#endif