//
// Created by Michael Wolhandler on 31/12/2020.
//
#include <iostream>
#include "Filters.h"
#include <cmath>
#define NUM_OF_SHADES 256
#define FACTOR_BLUR 16
#define FACTOR_SOBEL 8



/**
 * The function check if all the values of the matrix are between 0 and 255 if not they will tbe replaced by 0
 * if it is a negative number and or 255 if it superior of 255
 * @param matrix matrix that we check
 */
void CheckRange(Matrix& matrix){
    for (int i = 0; i <matrix.GetRows()* matrix.GetCols(); ++i) {
        if(matrix[i] > NUM_OF_SHADES - 1)
            matrix[i] = NUM_OF_SHADES -1;
        if(matrix[i] < 0)
            matrix[i] = 0;
    }
}

/**
 * The function returns a matrix after quantization
 * @param image Given matrix
 * @param levels Number of levels in the quantization
 * @return A new matrix that represents image after quantization
 */
Matrix Quantization(const Matrix& image,int levels){
    int scale = NUM_OF_SHADES / levels;
    int arr[NUM_OF_SHADES];
    int averages[NUM_OF_SHADES];
    int x = 0;
    for (int i = 0; i < levels; ++i) {
        arr[i]=x;
        x+= scale;
    }
    arr[levels] = x;
    for (int k = 0; k <levels ;++k){
        float x = (arr[k]+arr[k+1]-1)/2;
        averages[k] = x;
    }

    Matrix res (image.GetRows(), image.GetCols());
    for (int k = 0; k < image.GetCols()*image.GetRows() ; ++k) {
        for (int j = 0; j < levels; ++j) {
            if (image[k] >= (float) arr[j] && image[k]< (float) arr[j+1]){
                res[k]= (float) averages[j];
                break;
            }
        }
    }
    return res;
}

/**
 * The function creates a new matrix with a new row at the beginning and end of matrix1
 * and a new columns at the beginning and end of matrix1
 * @param matrix1 Given matrix
 * @return  a new matrix that is matrix1 surrounded by zeros
 */
Matrix MatrixWithZeros(const Matrix& matrix1){
    Matrix res(matrix1.GetRows()+2, matrix1.GetCols()+2);
    for (int k = 0; k <res.GetRows();++k){
        for (int m = 0; m < res.GetCols(); ++m) {
            if(k==0 || m == 0 || k == res.GetRows()-1 || m == res.GetCols()-1)
                res(k,m) = 0;
            else
                res(k,m) = matrix1(k-1,m-1);
        }
    }
    return res;
}

/**
 * The function returns the result of the convolution of the matrix1 and matrix2
 * @param matrix1 The matrix that we want to do the convolution
 * @param matrix2 A matrix of dimension 3*3
 * @param factor  number that we multiply with all the values of the new matrix
 * @return A matrix that is the result of the convolution of the matrix1 and matrix2
 */
Matrix Convolution(const Matrix& matrix1, const Matrix& matrix2,const float factor){
    Matrix temp = MatrixWithZeros(matrix1);
    Matrix res(matrix1.GetRows(), matrix1.GetCols());
    for (int i = 1; i <temp.GetRows()-1; ++i) {
        for (int j = 1; j < temp.GetCols()-1 ; ++j) {
            float x1 = matrix2(0,0) * temp(i-1,j-1);
            float x2 = matrix2(0,1) * temp(i-1,j);
            float x3 = matrix2(0,2) * temp(i-1,j+1);
            float x4 = matrix2(1,0) * temp(i,j-1);
            float x5 = matrix2(1,1) * temp(i,j);
            float x6 = matrix2(1,2) * temp(i,j+1);
            float x7 = matrix2(2,0) * temp(i+1,j-1);
            float x8 = matrix2(2,1) * temp(i+1,j);
            float x9 = matrix2(2,2) * temp(i+1,j+1);
            float total = factor * (x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8 + x9);
            total = rintf(total);
            res(i-1,j-1) = total;

        }
    }
    return res;
}

/**
 * the function returns the result of what the exercise asked to
 * @param image A matrix that we want to blur
 * @return the result of the blurring
 */
Matrix Blur(const Matrix& image){
   float blur_factor = 1.0/FACTOR_BLUR;
   Matrix conv_matrix(3,3);
   conv_matrix[0] = 1; conv_matrix[1] = 2; conv_matrix[2] = 1;
   conv_matrix[3] = 2; conv_matrix[4] = 4; conv_matrix[5] = 2;
   conv_matrix[6] = 1; conv_matrix[7] = 2; conv_matrix[8] = 1;
   Matrix x = Convolution(image,conv_matrix,blur_factor);
   CheckRange(x);
   return x;
}
/**
 * the function returns the result of what the exercise asked to
 * @param image A matrix that we want to sobel
 * @return the result of the sobel action
 */
Matrix Sobel(const Matrix& image){
    float sobel_factor = 1.0/FACTOR_SOBEL;
    Matrix conv_matrix1(3,3);
    conv_matrix1[0] = 1; conv_matrix1[1] = 0; conv_matrix1[2] = -1;
    conv_matrix1[3] = 2; conv_matrix1[4] = 0; conv_matrix1[5] = -2;
    conv_matrix1[6] = 1; conv_matrix1[7] = 0; conv_matrix1[8] = -1;

    Matrix conv_matrix2(3,3);
    conv_matrix2[0] = 1; conv_matrix2[1] = 2; conv_matrix2[2] = 1;
    conv_matrix2[3] = 0; conv_matrix2[4] = 0; conv_matrix2[5] = 0;
    conv_matrix2[6] = -1; conv_matrix2[7] = -2; conv_matrix2[8] = -1;

    Matrix m1 = Convolution(image,conv_matrix1,sobel_factor);
    Matrix m2 = Convolution(image,conv_matrix2,sobel_factor);
    m1 += m2;
    CheckRange(m1);
    return m1;
}