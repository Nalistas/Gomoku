/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Matrix
*/

#include <vector>
#include <ostream>
#include <functional>

#ifndef MATRIX_HPP_
    #define MATRIX_HPP_

class Matrix {
    public:

        Matrix(unsigned int x = 20, unsigned int y = 20);
        Matrix(const Matrix &other);
        ~Matrix() = default;

        double &operator()(unsigned int x, unsigned int y);
        double operator()(unsigned int x, unsigned int y) const;
        Matrix &operator=(const Matrix &other);
        Matrix &operator+=(const Matrix &other);
        Matrix operator+(const Matrix &other);
        Matrix operator*(const Matrix &other) const;
        Matrix &operator*=(double x);
        Matrix operator*(double x) const;
        Matrix operator-(const Matrix &other) const;
        Matrix &operator-=(const Matrix &other);

        double sum() const; 

        unsigned int rows() const;
        unsigned int cols() const;

        Matrix cwiseProduct(const Matrix &other) const;
        Matrix transpose() const;
        double determinant() const;
        Matrix inverse() const;
        Matrix &unaryExpr(std::function<double(double)> func);

    private:
        double determinantHelper(const Matrix &m) const;
        Matrix getSubMatrix(const Matrix &m, unsigned int row, unsigned int col) const;
        Matrix inverseHelper(const Matrix &m, double det) const;


        unsigned int _rows;
        unsigned int _cols;
        std::vector<std::vector<double>> _data;
};

std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

#endif
