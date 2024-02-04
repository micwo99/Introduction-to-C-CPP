// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>


// Insert Matrix class here...
/**
 * Class that represents a matrix
 */
class Matrix
{
private:
    int rows;
    int cols;
    float *values;
public:
    // Constructors
    /**
     * Constructor of the matrix that receives two arguments, the number of rows and columns
     * the constructor initialized the values of the matrix with 0
     * @param rows Number of rows
     * @param cols Number of columns
     */
    Matrix(int rows, int cols);
    /**
     * Default constructor initialized a matrix of dimension 1*1 with 0 as value in the matrix
     */
    Matrix() : Matrix(1, 1){
    };
    /**
     * Copy constructor of a matrix
     * @param other Matrix that we want to copy
     */
    Matrix(const Matrix& other);
    /**
     * Destructor of the matrix that delete all the values of the matrix
     */
    ~Matrix();

    /**
     * The function returns the number of rows in the matrix
     * @return number of rows
     */
    int GetRows() const {
        return rows; }

   /**
   * The function returns the number of columns in the matrix
   * @return number of columns
   */
    int GetCols() const {
        return cols; }

    /**
     * The function transforms a matrix into a column vector.
     * @return matrix after vectorization
     */
    Matrix& Vectorize();

    /**
     * the function print the matrix
     */
    void Print() const;

    /**
     * Overloaded operator = that changes the parameters of the matrix to the parameters of the matrixt rhs
     * @param rhs Matrix
     * @return a reference of recently changed matrix
     */
    Matrix& operator=(const Matrix& rhs);
    /**
     * Overloaded operator * returns the result of a matrix multiplication
     * @param lhs The left matrix
     * @param rhs The right matrix
     * @return A new matrix
     */
    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

    /**
     * Overloaded operator * returns the result of a matrix multiplication with a scalar
     * @param lhs Left matrix
     * @param c  Scalar
     * @return  A new matrix
    */
    friend Matrix operator*(const Matrix& lhs, const float& c);

    /**
     * Overloaded operator * returns the result of a matrix multiplication with a scalar
     * @param c Scalar
     * @param rhs Right Matrix
     * @return A new matrix
     */
    friend Matrix operator*(const float& c, const Matrix& rhs);

    /**
     * Overloaded operator *= returns the the given matrix after multiplication with rhs
     * @param rhs Right matrix
     * @return the given matrix
     */
    Matrix& operator*=(const Matrix& rhs);

    /**
     * Overloaded operator *= returns the the given matrix after multiplication with the scalar c
     * @param c Scalar
     * @return The given matrix
     */
    Matrix& operator*=(const float& c);

    /**
     * Overloaded operator / returns the result of a matrix division with a scalar
     * @param lhs Left matrix
     * @param c  Scalar
     * @return  A new matrix if c is different from 0
     */
    friend Matrix operator/(const Matrix& lhs, const float& c);
    /**
     * Overloaded operator /= returns the the given matrix after division with the scalar c
     * @param c Scalar
     * @return The given matrix if c is different from 0
     */
    Matrix& operator/=(const float& c);

    /**
     * Overloaded operator + return the addition of two matrix
     * @param lhs Left matrix
     * @param rhs  Right matrix
     * @return A new matrix
     */
    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);

    /**
     * Overloaded operator += returns the given matrix after the addition with rhs
     * @param rhs Right matrix
     * @return The given matrix
     */
    Matrix& operator+=(const Matrix& rhs);

  /**
   * Overloaded operator += returns the given matrix after the addition with rthe scalar c
   * @param c Scalar
   * @return The given matrix
   */
    Matrix& operator+=(const float& c);

    /**
     * Overloaded operator() returns the values at the given row and columns
     * @param row  A row
     * @param col  A columns
     * @return  A value of the matrix
     */
    float& operator()(int row, int col) const;

    /**
     * Overloaded operator[] returns the value at the given coordinate
     * @param coord  Number between 0 and the number of values in the matrix
     * @return  The value of the matrix at coord
     */
    float& operator[](int coord) const;

    /**
     * Overloaded operator== check if two matrix are the same
     * @param lhs Left matrix
     * @param rhs  Right matrix
     * @return true/false
     */
    friend bool operator==(const Matrix &lhs, const Matrix &rhs);

    /**
     * Overloaded operator!= check if two matrix are not the same
     * @param lhs Left matrix
     * @param rhs  Right matrix
     * @return true/false
     */
    friend bool operator!=(const Matrix &lhs, const Matrix &rhs);

    /**
     * Overloaded operator<< print the given matrix
     * @param os the file to read
     * @param matrix matrix that we want to print
     * @return A reference to the istream file
     */
    friend std::ostream& operator<<(std::ostream &os, const Matrix& matrix);

    /**
     * Overloaded operator>> create a new matrix depends on the input of the user
     * @param in The file to read
     * @param matrix the matrix where the value will be assigned
     * @return A reference to the istream file
     */
    friend std::istream& operator>>(std::istream &in, const Matrix& matrix);

};

#endif //MATRIX_H
