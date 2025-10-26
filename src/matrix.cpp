#include "../include/matrix.h"


Matrix::Matrix() : rows_(0), cols_(0), data_() {}

Matrix::Matrix(int rows_, int cols_) : rows_(rows_), cols_(cols_), data_(rows_*cols_, 0.0f) {}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}


double& Matrix::operator()(int i, int j) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range.");
    }
    return data_[i * cols_ + j];
}

const double& Matrix::operator()(int i , int j) const {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range.");
    }
    return data_[i * cols_ + j];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = other.data_;
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows_ == other.rows_ || cols_ == other.cols_) {
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < data_.size(); i++) {
            result.data_[i] = data_[i] + other.data_[i];
        }
        return result;

    } else if (other.rows_ == 1 && other.cols_ == cols_) {
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                result(i, j) = (*this)(i, j) + other(0, j);
            }
        }
        return result;
    }
    
    throw std::invalid_argument("Dimension mismatch in addition.");
    
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Dimension mismatch in addition.");
    }

    Matrix result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); i++) {
        result.data_[i] = data_[i] - other.data_[i];
    }

    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Dimension mismatch in multiplication.");
    }

    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            double sum = 0.0;
            for (int k = 0; k < cols_; k++) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i,j) = sum;
        }
    }

    return result;
}

Matrix Matrix::operator*(const double k) const {
    Matrix result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); i++) {
        result.data_[i] = data_[i] * k;
    }

    return result;
}

Matrix operator*(const double k, const Matrix& M) {
    return M * k;
}

Matrix Matrix::operator/(const Matrix& other) const {
    if (rows_ == other.rows_ && cols_ == other.cols_) {
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < data_.size(); i++) {
            result.data_[i] = data_[i] / other.data_[i];
        }
        return result;
    } else if (rows_ == other.rows_ && other.cols_ == 1) {
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                result(i, j) = (*this)(i, j) / other(i, 0);
            }
        }
        return result;
    } else if (other.rows_ == 1 && cols_ == other.cols_) {
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                result(i, j) = (*this)(i, j) / other(0, j);
            }
        }
        return result;
    }

    throw std::invalid_argument("Dimension mismatch in division.");
}

Matrix Matrix::operator/(double scalar) const {
    Matrix result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); ++i)
        result.data_[i] = data_[i] / scalar;
    return result;
}


Matrix& Matrix::operator+=(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Dimension mismatch for +=.");
    }

    for (size_t i = 0; i < data_.size(); i++) {
        data_[i] += other.data_[i];
    }

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Dimension mismatch for -=.");
    }

    for (size_t i = 0; i < data_.size(); i++) {
        data_[i] -= other.data_[i];
    }

    return *this;
}

Matrix& Matrix::operator*=(const double k) {
    for(size_t i = 0; i < data_.size(); i++) {
        data_[i] *= k;
    }

    return *this;
}

Matrix& Matrix::operator/=(const double k) {
    for (size_t i = 0; i < data_.size(); i++) {
        data_[i] /= k;
    }

    return *this;
}


Matrix Matrix::random(int rows_, int cols_, double mean = 0.0f, double std = 1.0f) {
    assert((rows_ != 0 && cols_ != 0) && "rows_ and columns must be greater tha 0!");
    Matrix result(rows_, cols_);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(mean, std);
    for (double &d : result.data_) {
        d = dist(gen);
    }
    return result;
}

Matrix Matrix::hadamard(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Dimension mismatch in dot product.");
    }

    Matrix result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); i++) {
        result.data_[i] = data_[i] * other.data_[i];
    }

    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result(j, i) = (*this)(i, j);
        }
    }

    return result;
}

Matrix Matrix::maximum(double scalar) const {
    Matrix result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); i++) {
        result.data_[i] = std::max(data_[i], scalar);
    }
    return result;
}

Matrix Matrix::maximum(const Matrix& other) const {
    if (rows_ == other.rows_ && cols_ == other.cols_) {
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < data_.size(); i++) {
            result.data_[i] = std::max(data_[i], other.data_[i]);
        }
        return result;
    } else if (other.rows_ == 1 && other.cols_ == cols_) {
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                result(i, j) = std::max((*this)(i, j), other(0, j));
            }
        }
        return result;
    }
}

Matrix Matrix::exp() const {
    Matrix result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = std::exp(data_[i]);
    }
    return result;
}

Matrix Matrix::clipped(double min_val, double max_val) const {
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result(i, j) = std::clamp((*this)(i, j), min_val, max_val);
        }
    }
    return result;
}

Matrix Matrix::sumRows() const {
    Matrix out(rows_, 1);

    for (int i = 0; i < rows_; i++) {
        double sum = 0.0;
        for (int j = 0; j < cols_; j++) {
            sum += (*this)(i, j);
        }
        out(i, 0) = sum;
    }

    return out;
}

Matrix Matrix::sumCols() const {
    Matrix out(1, cols_);
    
    for (int i = 0; i < cols_; i++) {
        double sum = 0.0;
        for (int j = 0; j < rows_; j++) {
            sum += (*this)(j, i);
        }
        out(0, i) = sum;
    }

    return out;
}

Matrix Matrix::maxRows() const {
    Matrix result(rows_, 1);

    for (int i = 0; i < rows_; i++) {
        double max_val = (*this)(i, 0);
        for (int j = 1; j < cols_; j++) {
            max_val = std::max(max_val, (*this)(i, j));
        }
        result(i, 0) = max_val;
    }
    return result;
}

Matrix Matrix::maxCols() const {
    Matrix result(1, cols_);

    for (int j = 0; j < cols_; j++) {
        double max_val = (*this)(0, j);
        for (int i = 0; i < rows_; i++) {
            max_val = std::max(max_val, (*this)(i, j));
        }
        result(0, j) = max_val;
    }
    return result;;
}

int Matrix::getSize() const { return data_.size(); }
int Matrix::getRows() const { return rows_; }
int Matrix::getCols() const { return cols_; }

std::ostream& operator<<(std::ostream& os, const Matrix& M) {
    os << std::endl << "[";
    for (int i = 0; i < M.rows_; i++) {
        os << "[ ";
        for (int j = 0; j < M.cols_; j++) {
            os << std::setw(8) << M(i, j) << " ";
        }
        os << " ]";

        if (i != (M.rows_ - 1)) {
            os << "," << std::endl << " ";
        }
    }
    os << "]" << std::endl;

    return os;
}