#ifndef __MIXED_OPERATORS__H__
#define __MIXED_OPERATORS__H__

#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"

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

#endif  //!__MIXED_OPERATORS__H__