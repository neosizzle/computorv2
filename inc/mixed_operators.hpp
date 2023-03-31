#ifndef __MIXED_OPERATORS__H__
#define __MIXED_OPERATORS__H__

#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "Matrix.hpp"

/**
 * @brief Additional operators for imaginary numbers
 * 
 */

// imaginary + rational
ImaginaryNumber operator + (ImaginaryNumber lhs, RationalNumber rhs);

// imaginary - rational
ImaginaryNumber operator - (ImaginaryNumber lhs, RationalNumber rhs);

// imaginary * rational
ImaginaryNumber operator * (ImaginaryNumber lhs, RationalNumber rhs);

// imaginary / rational
ImaginaryNumber operator / (ImaginaryNumber lhs, RationalNumber rhs);

// imaginary ^ rational
ImaginaryNumber operator ^ (ImaginaryNumber lhs, RationalNumber rhs);

// imaginary + matrix
// imaginary - matrix

// imaginary * matrix
Matrix operator * (ImaginaryNumber lhs, Matrix rhs);

// imaginary / matrix
Matrix operator / (ImaginaryNumber lhs, Matrix rhs);


/**
 * @brief Additional operators for rational numbers
 * 
 */

// rational + imaginary
ImaginaryNumber operator + (RationalNumber lhs, ImaginaryNumber rhs);

// rational - imaginary
ImaginaryNumber operator - (RationalNumber lhs, ImaginaryNumber rhs);

// rational * imaginary
ImaginaryNumber operator * (RationalNumber lhs, ImaginaryNumber rhs);

// rational / imaginary
ImaginaryNumber operator  / (RationalNumber lhs, ImaginaryNumber rhs);

// rational + matrix
// rational - matrix

// rational * matrix
Matrix operator * (RationalNumber lhs, Matrix rhs);

// rational / matrix
Matrix operator / (RationalNumber lhs, Matrix rhs);


/**
 * @brief Additional operators for matrices
 * 
 */
//  matrix + rational
//  matrix - rational

//  matrix * rational
Matrix operator * (Matrix lhs, RationalNumber rhs);

//  matrix / rational
Matrix operator / (Matrix lhs, RationalNumber rhs);

// matrix * imaginary
Matrix operator * (Matrix lhs, ImaginaryNumber rhs);

// matrix / imaginary
Matrix operator / (Matrix lhs, ImaginaryNumber rhs);

#endif  //!__MIXED_OPERATORS__H__