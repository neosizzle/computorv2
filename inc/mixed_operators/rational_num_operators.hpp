#ifndef __RATIONAL_NUM_OPERATORS__H__
#define __RATIONAL_NUM_OPERATORS__H__
#include "ImaginaryNum.hpp"
#include "RationalNum.hpp"

ImaginaryNumber operator + (RationalNumber lhs, ImaginaryNumber rhs);
ImaginaryNumber operator - (RationalNumber lhs, ImaginaryNumber rhs);
ImaginaryNumber operator * (RationalNumber lhs, ImaginaryNumber rhs);
ImaginaryNumber operator / (RationalNumber lhs, ImaginaryNumber rhs);

#endif  //!__RATIONAL_NUM_OPERATORS__H__