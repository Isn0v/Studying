// SquareMatrix.h
#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include <vector>
#include <cstddef>

class SquareMatrix {
private:
    std::vector<std::vector<double>> matrix; 
    size_t size;

public:
    explicit SquareMatrix(size_t size);
    SquareMatrix(const std::vector<double>& values);
    void set(size_t row, size_t col, double value); 
    double get(size_t row, size_t col) const; 
    void print() const;
    double determinant() const;

    explicit operator double() const {
        return determinant();
    }

    SquareMatrix operator+(const SquareMatrix& other) const {
        SquareMatrix result(size);
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    // Overloaded operator += for compound addition
    SquareMatrix& operator+=(const SquareMatrix& other) {
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                matrix[i][j] += other.matrix[i][j];
            }
        }
        return *this;
    }

    // Overloaded operator * for multiplying two matrices
    SquareMatrix operator*(const SquareMatrix& other) const {
        SquareMatrix result(size);
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                for (size_t k = 0; k < size; k++) {
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return result;
    }

    // Overloaded operator * for multiplying a matrix by a scalar
    SquareMatrix operator*(double scalar) const {
        SquareMatrix result(size);
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                result.matrix[i][j] = matrix[i][j] * scalar;
            }
        }
        return result;
    }

    // Overloaded operator *= for compound multiplication by a scalar
    SquareMatrix& operator*=(double scalar) {
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                matrix[i][j] *= scalar;
            }
        }
        return *this;
    }

    // Overloaded operator == for equality check
    bool operator==(const SquareMatrix& other) const {
        return matrix == other.matrix; // Assuming matrix is a vector of vectors
    }

    // Overloaded operator != for inequality check
    bool operator!=(const SquareMatrix& other) const {
        return !(*this == other);
    }
};

#endif // SQUAREMATRIX_H