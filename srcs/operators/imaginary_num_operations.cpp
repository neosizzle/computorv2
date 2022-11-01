#include "main.hpp"

/**
 * @brief Additional operators for rational numbers
 * 
 */

// imaginary + rational
ImaginaryNumber operator + (ImaginaryNumber lhs, RationalNumber rhs)
{
	ImaginaryNumber res(lhs);

	if (rhs.is_float)
		res.real_part = lhs.real_part + RationalNumber(rhs.float_value);
	else
		res.real_part = lhs.real_part + RationalNumber(rhs.int_value);
	return res;
}


// imaginary - rational
ImaginaryNumber operator - (ImaginaryNumber lhs, RationalNumber rhs)
{
	ImaginaryNumber res(lhs);

	if (rhs.is_float)
		res.real_part = lhs.real_part - RationalNumber(rhs.float_value);
	else
		res.real_part = lhs.real_part - RationalNumber(rhs.int_value);
	return res;
}


// imaginary * rational
ImaginaryNumber operator * (ImaginaryNumber lhs, RationalNumber rhs)
{
	ImaginaryNumber res(lhs);

	if (rhs.is_float)
		res.real_part = lhs.real_part * RationalNumber(rhs.float_value);
	else
		res.real_part = lhs.real_part * RationalNumber(rhs.int_value);
	return res;
}


// imaginary / rational
ImaginaryNumber operator / (ImaginaryNumber lhs, RationalNumber rhs)
{
	ImaginaryNumber res(lhs);

	if (rhs.is_float)
		res.real_part = lhs.real_part / RationalNumber(rhs.float_value);
	else
		res.real_part = lhs.real_part / RationalNumber(rhs.int_value);
	return res;
}


// imaginary ^ rational
ImaginaryNumber operator ^ (ImaginaryNumber lhs, RationalNumber rhs)
{
	ImaginaryNumber res(lhs);

	if (rhs.is_float)
		res.real_part = lhs.real_part ^ RationalNumber(rhs.float_value);
	else
		res.real_part = lhs.real_part ^ RationalNumber(rhs.int_value);
	return res;
}