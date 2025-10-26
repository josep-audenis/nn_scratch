#include "../include/matrix.h"


Matrix::Matrix() : rows(0), cols(0), data() {}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows*cols, 0.0f) {}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(other.data) {}


float& Matrix::operator()(int i, int j) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Index out of range.");
    }
    return data[i * cols + j];
}

const float& Matrix::operator()(int i , int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Index out of range.");
    }
    return data[i * cols + j];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = other.data;
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows == other.rows || cols == other.cols) {
        Matrix result(rows, cols);
        for (size_t i = 0; i < data.size(); i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;

    } else if (other.rows == 1 && other.cols == cols) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = (*this)(i, j) + other(0, j);
            }
        }
        return result;
    }
    
    throw std::invalid_argument("Dimension mismatch in addition.");
    
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimension mismatch in addition.");
    }

    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); i++) {
        result.data[i] = data[i] - other.data[i];
    }

    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Dimension mismatch in multiplication.");
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            float sum = 0.0f;
            for (int k = 0; k < cols; k++) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i,j) = sum;
        }
    }

    return result;
}

Matrix Matrix::operator*(const float k) const {
    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); i++) {
        result.data[i] = data[i] * k;
    }

    return result;
}

Matrix operator*(const float k, const Matrix& M) {
    return M * k;
}

Matrix Matrix::operator/(const Matrix& other) const {
    if (rows == other.rows && cols == other.cols) {
        Matrix result(rows, cols);
        for (size_t i = 0; i < data.size(); i++) {
            result.data[i] = data[i] / other.data[i];
        }
        return result;
    } else if (rows == other.rows && other.cols == 1) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = (*this)(i, j) / other(i, 0);
            }
        }
        return result;
    } else if (other.rows == 1 && cols == other.cols) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = (*this)(i, j) / other(0, j);
            }
        }
        return result;
    }

    throw std::invalid_argument("Dimension mismatch in division.");
}

Matrix Matrix::operator/(float scalar) const {
    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); ++i)
        result.data[i] = data[i] / scalar;
    return result;
}


Matrix& Matrix::operator+=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimension mismatch for +=.");
    }

    for (size_t i = 0; i < data.size(); i++) {
        data[i] += other.data[i];
    }

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimension mismatch for -=.");
    }

    for (size_t i = 0; i < data.size(); i++) {
        data[i] -= other.data[i];
    }

    return *this;
}

Matrix& Matrix::operator*=(const float k) {
    for(size_t i = 0; i < data.size(); i++) {
        data[i] *= k;
    }

    return *this;
}

Matrix& Matrix::operator/=(const float k) {
    for (size_t i = 0; i < data.size(); i++) {
        data[i] /= k;
    }

    return *this;
}


Matrix Matrix::random(int rows, int cols, float mean = 0.0f, float std = 1.0f) {
    assert((rows != 0 && cols != 0) && "Rows and columns must be greater tha 0!");
    Matrix result(rows, cols);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(mean, std);
    for (float &d : result.data) {
        d = dist(gen);
    }
    return result;
}

Matrix Matrix::hadamard(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimension mismatch in dot product.");
    }

    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); i++) {
        result.data[i] = data[i] * other.data[i];
    }

    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(j, i) = (*this)(i, j);
        }
    }

    return result;
}

Matrix Matrix::maximum(float scalar) const {
    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); i++) {
        result.data[i] = std::max(data[i], scalar);
    }
    return result;
}

Matrix Matrix::maximum(const Matrix& other) const {
    if (rows == other.rows && cols == other.cols) {
        Matrix result(rows, cols);
        for (size_t i = 0; i < data.size(); i++) {
            result.data[i] = std::max(data[i], other.data[i]);
        }
        return result;
    } else if (other.rows == 1 && other.cols == cols) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = std::max((*this)(i, j), other(0, j));
            }
        }
        return result;
    }
}

Matrix Matrix::exp() const {
    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); ++i) {
        result.data[i] = std::exp(data[i]);
    }
    return result;
}

Matrix Matrix::sumRows() const {
    Matrix out(rows, 1);

    for (int i = 0; i < rows; i++) {
        float sum = 0.0f;
        for (int j = 0; j < cols; j++) {
            sum += (*this)(i, j);
        }
        out(i, 0) = sum;
    }

    return out;
}

Matrix Matrix::sumCols() const {
    Matrix out(1, cols);
    
    for (int i = 0; i < cols; i++) {
        float sum = 0.0f;
        for (int j = 0; j < rows; j++) {
            sum += (*this)(j, i);
        }
        out(0, i) = sum;
    }

    return out;
}

Matrix Matrix::maxRows() const {
    Matrix result(rows, 1);

    for (int i = 0; i < rows; i++) {
        float max_val = (*this)(i, 0);
        for (int j = 1; j < cols; j++) {
            max_val = std::max(max_val, (*this)(i, j));
        }
        result(i, 0) = max_val;
    }
    return result;
}

Matrix Matrix::maxCols() const {
    Matrix result(1, cols);

    for (int j = 0; j < cols; j++) {
        float max_val = (*this)(0, j);
        for (int i = 0; i < rows; i++) {
            max_val = std::max(max_val, (*this)(i, j));
        }
        result(0, j) = max_val;
    }
    return result;;
}

int Matrix::getRows() const { return rows; }
int Matrix::getCols() const { return cols; }

std::ostream& operator<<(std::ostream& os, const Matrix& M) {
    os << std::endl << "[";
    for (int i = 0; i < M.rows; i++) {
        os << "[ ";
        for (int j = 0; j < M.cols; j++) {
            os << std::setw(8) << M(i, j) << " ";
        }
        os << " ]";

        if (i != (M.rows - 1)) {
            os << "," << std::endl << " ";
        }
    }
    os << "]" << std::endl;

    return os;
}