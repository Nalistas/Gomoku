/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Matrix
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Matrix.hpp"

 
Matrix::Matrix(unsigned int x, unsigned int y) :
    _rows(x), _cols(y), _data(x, std::vector<double>(y, 0.0))
{}

Matrix::Matrix(const Matrix &other) : _rows(other._rows), _cols(other._cols), _data(other._data) {}

double &Matrix::operator()(unsigned int x, unsigned int y)
{
    if (x >= _rows || y >= _cols) {
        throw std::out_of_range("Index out of range");
    }
    return _data[x][y];
}

double Matrix::operator()(unsigned int x, unsigned int y) const
{
    if (x >= _rows || y >= _cols) {
        throw std::out_of_range("Index out of range");
    }
    return _data[x][y];
}

Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other) {
        _rows = other._rows;
        _cols = other._cols;
        _data = other._data;
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    if (_cols != other._rows) {
        std::cerr << "this " << _cols << " other " << other._rows << std::endl;
        throw std::invalid_argument("Matrix dimensions must agree for multiplication");
    }

    Matrix result(_rows, other._cols);

    for (unsigned int i = 0; i < _rows; ++i) {
        for (unsigned int j = 0; j < other._cols; ++j) {
            for (unsigned int k = 0; k < _cols; ++k) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}

unsigned int Matrix::rows() const {
    return _rows;
}

unsigned int Matrix::cols() const {
    return _cols;
}

Matrix Matrix::cwiseProduct(const Matrix& other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrices must have the same dimensions for element-wise multiplication");
    }

    Matrix result(_rows, _cols);
    for (unsigned int i = 0; i < _rows; ++i) {
        for (unsigned int j = 0; j < _cols; ++j) {
            result(i, j) = (*this)(i, j) * other(i, j);
        }
    }
    return result;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition");
    }
    for (unsigned int i = 0; i < _rows; ++i) {
        for (unsigned int j = 0; j < _cols; ++j) {
            (*this)(i, j) += other(i, j);
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &other) {
    Matrix result(*this);
    result += other;
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (unsigned int i = 0; i < matrix.rows(); ++i) {
        for (unsigned int j = 0; j < matrix.cols(); ++j) {
            os << matrix(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

Matrix Matrix::transpose() const
{
    Matrix result(_cols, _rows);
    for (unsigned int i = 0; i < _rows; ++i) {
        for (unsigned int j = 0; j < _cols; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}


double Matrix::determinant() const
{
    if (_rows != _cols) {
        throw std::invalid_argument("Determinant is only defined for square matrices");
    }
    return determinantHelper(*this);
}


Matrix Matrix::inverse() const
{
    if (_rows != _cols) {
        throw std::invalid_argument("Inverse is only defined for square matrices");
    }
    double det = determinant();
    if (std::abs(det) < 1e-9) {
        throw std::invalid_argument("Matrix is singular and cannot be inverted");
    }
    return inverseHelper(*this, det);
}

double Matrix::determinantHelper(const Matrix& m) const
{
    if (m.rows() == 1) {
        return m(0, 0);
    }

    double det = 0.0;
    for (unsigned int i = 0; i < m.cols(); ++i) {
        Matrix subMatrix = getSubMatrix(m, 0, i);
        det += (i % 2 == 0 ? 1 : -1) * m(0, i) * subMatrix.determinantHelper(subMatrix);
    }
    return det;
}


Matrix Matrix::getSubMatrix(const Matrix& m, unsigned int row, unsigned int col) const
{
    Matrix subMatrix(m.rows() - 1, m.cols() - 1);
    unsigned int subRow = 0;
    for (unsigned int i = 0; i < m.rows(); ++i) {
        if (i == row) continue;
        unsigned int subCol = 0;
        for (unsigned int j = 0; j < m.cols(); ++j) {
            if (j == col) continue;
            subMatrix(subRow, subCol) = m(i, j);
            subCol++;
        }
        subRow++;
    }
    return subMatrix;
}


Matrix Matrix::inverseHelper(const Matrix& m, double det) const
{
    if (m.rows() == 2) {
        Matrix result(2, 2);
        result(0, 0) = m(1, 1) / det;
        result(0, 1) = -m(0, 1) / det;
        result(1, 0) = -m(1, 0) / det;
        result(1, 1) = m(0, 0) / det;
        return result;
    }
    throw std::invalid_argument("Inverse method not implemented for matrices larger than 2x2");
}

Matrix &Matrix::unaryExpr(std::function<double(double)> func)
{
    for (unsigned int i = 0; i < _rows; ++i) {
        for (unsigned int j = 0; j < _cols; ++j) {
            (*this)(i, j) = func((*this)(i, j));
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(double x)
{
    for (unsigned int i = 0; i < _rows; ++i) {
        for (unsigned int j = 0; j < _cols; ++j) {
            (*this)(i, j) *= x;
        }
    }
    return *this;
}

Matrix Matrix::operator*(double x) const
{
    Matrix result(*this);
    result *= x;
    return result;
}

Matrix &Matrix::operator-=(Matrix const &other)
{
    if (this->_cols != other._cols || this->_rows != other._rows) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
    }
    for (unsigned int i = 0; i < _rows; ++i) {
        for (unsigned int j = 0; j < _cols; ++j) {
            (*this)(i, j) -= other(i, j);
        }
    }
    return *this;
}

Matrix Matrix::operator-(Matrix const &other) const
{
    Matrix result(*this);
    result -= other;
    return result;
}

double Matrix::sum() const
{
    double result = 0;

    for (unsigned int i = 0; i < this->_rows; ++i) {
        for (unsigned int j = 0; j < this->_cols; ++j) {
            result += (*this)(i, j);
        }
    }
    return result;
}
