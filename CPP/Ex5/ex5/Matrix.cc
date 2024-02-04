//
// Created by Michael Wolhandler on 28/12/2020.
//
#include <iostream>


#define DIMENSION_PB "Invalid matrix dimensions.\n"
#define DIVISION_ERR "Division by zero.\n"
#define INVALID_RANGE "Index out of range.\n"
#define FILE_ERROR "Error loading from input stream.\n"

#include "Matrix.h"
#include "MatrixException.h"



Matrix::Matrix(int row, int col): rows(row), cols(col){
    if (cols <= 0 || rows <= 0)
    {
        throw MatrixException(DIMENSION_PB);
    }
    try{
    values= new float[row * cols];
    }
    catch (std::bad_alloc &e) {
        throw MatrixException("Allocation failed.\n");
    }

    for (int i = 0;i < row * cols; ++i) {
        values[i]=0;
    }
}


Matrix::Matrix(const Matrix &m) : rows(m.rows), cols(m.cols){

    try{
        values= new float[rows * cols];
    }
    catch (std::bad_alloc &e) {
        throw MatrixException("Allocation failed.\n");
    }
    for (int i = 0;i < rows * cols; ++i){
        values[i] = m.values[i];
    }

}

Matrix :: ~Matrix(){
    delete []values;
}

Matrix &Matrix::Vectorize(){
    this->rows= rows * cols;
    this ->cols = 1;
    return *this;
}

void Matrix::Print() const{
    for (int i = 0; i <rows * cols ; ++i) {
        if ((i+1) % cols != 0 ||(i==0 && cols !=1)){
            std::cout << values[i]<< " ";
        }
        else {
            std::cout << values[i] << std ::endl;
        }

    }
}

Matrix &Matrix::operator=(const Matrix& rhs){
    if( this != &rhs){
        delete [] values;
        rows = rhs.rows;
        cols = rhs.cols;
        try{
            values= new float[rows * cols];
        }
        catch (std::bad_alloc &e) {
            throw MatrixException("Allocation failed.\n");
        }
        for (int i = 0; i < cols * rows; i++)
        {
            values[i] = rhs[i];
        }
    }
    return *this;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs)
{
    if(lhs.cols !=rhs.rows)
    {
        throw MatrixException(DIMENSION_PB);
    }
    Matrix matrix(lhs.rows,rhs.cols);
    for (int i = 0; i <lhs.rows; ++i)
    {

        for (int k = 0; k <rhs.cols; ++k)
        {
            float res = 0;
            for (int m = 0; m <lhs.cols ; ++m)
            {
                res += lhs[i * lhs.cols + m] * rhs[m * rhs.cols + k];
            }
            matrix[i * rhs.cols + k] = res;
        }
    }
    return matrix;

}


Matrix operator*(const Matrix &lhs, const float &c) {
    Matrix res(lhs);
    for (int i = 0; i <lhs.rows * lhs.cols ; ++i) {
        res.values[i] = lhs[i] * c;
      }
      return res;

}

Matrix operator*(const float &c, const Matrix &rhs) {
    Matrix res(rhs);
    int num_ind = res.GetCols() * res.GetRows();
    for (int i=0; i<num_ind;++i){
        res.values[i] *= c;
    }
    return res;
}

Matrix &Matrix:: operator*=(const Matrix &rhs) {
    *this = *this * rhs;
    return *this;
}

Matrix &Matrix::operator*=(const float &c) {
    *this= *this * c;
    return *this;
}

Matrix operator/(const Matrix &lhs, const float &c) {
    if(c==0) {
        throw MatrixException(DIVISION_ERR);
    }
    Matrix res(lhs);
    for (int i = 0; i < lhs.rows * lhs.cols; ++i) {
        res[i] = lhs[i] / c;
    }
    return res;

}

Matrix &Matrix::operator/=(const float &c) {
    if(c==0){
        throw MatrixException(DIVISION_ERR);
    }
    *this= *this / c;
    return *this;

}

Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols) {
        throw MatrixException(DIMENSION_PB);
    }
    Matrix res(lhs);
    for (int i = 0; i < res.rows * res.cols; ++i) {
        res[i] += rhs[i];
    }
    return res;

}

Matrix &Matrix::operator+=(const Matrix &rhs) {

    if (rows != rhs.rows || cols != rhs.cols) {
        throw MatrixException(DIMENSION_PB);
    }
    for (int i = 0; i < rows * cols; ++i) {
        values[i] = values[i] + rhs[i];
    }
    return *this;


}

Matrix &Matrix::operator+=(const float &c) {
    for (int i = 0; i <rows*cols ; ++i) {
        values[i]+=c;
    }
    return *this;
}

float &Matrix::operator()(int row, int col) const {
    if( 0 > row || row >= rows || 0 >col || col >= cols){
        throw MatrixException(INVALID_RANGE);
    }

    return values[row * cols +col];

}

float &Matrix::operator[](int index) const {
    if(0>index|| index >= rows*cols){
        throw MatrixException(INVALID_RANGE);
    }
    return values[index];
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
    if(lhs.rows == rhs.rows && lhs.cols == rhs.cols){
        for (int i = 0; i < lhs.rows*lhs.cols ; ++i) {
            if (lhs[i]!= rhs[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool operator!=(const Matrix &lhs, const Matrix &rhs) {

    if(lhs.rows == rhs.rows && lhs.cols == rhs.cols){
        for (int i = 0; i < lhs.rows*lhs.cols ; ++i) {
            if (lhs[i]!= rhs[i]){
                return true ;
            }
        }
        return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (int i = 0; i <matrix.rows ; ++i) {
        for (int j = 0; j < matrix.cols; ++j)
        {
           os <<matrix[i * matrix.cols + j]<<' ';

        }
        os << std::endl;
    }
    return os;
}

std::istream &operator>>(std::istream &in, const Matrix &matrix) {
    if (!in.good())
    {
        throw MatrixException(FILE_ERROR);
    }
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {

            in >> matrix(i, j);

        }
    }
    return in;
}