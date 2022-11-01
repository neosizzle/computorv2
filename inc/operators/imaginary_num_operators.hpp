#ifndef __IMAGINARY_NUM_OPERATORS__H__
#define __IMAGINARY_NUM_OPERATORS__H__

ImaginaryNumber operator + (ImaginaryNumber lhs, RationalNumber rhs);
ImaginaryNumber operator - (ImaginaryNumber lhs, RationalNumber rhs);
ImaginaryNumber operator * (ImaginaryNumber lhs, RationalNumber rhs);
ImaginaryNumber operator / (ImaginaryNumber lhs, RationalNumber rhs);
ImaginaryNumber operator ^ (ImaginaryNumber lhs, RationalNumber rhs);

#endif  //!__IMAGINARY_NUM_OPERATORS__H__