#include "main.hpp"

/**
 * @brief Additional operators for rational numbers
 * 
 */

// rational + imaginary
ImaginaryNumber operator + (RationalNumber lhs, ImaginaryNumber rhs)
{
	ImaginaryNumber res(rhs);

	if (lhs.is_float)
		res.real_part = rhs.real_part + RationalNumber(lhs.float_value);
	else
		res.real_part = rhs.real_part + RationalNumber(lhs.int_value);
	return res;
}

// rational - imaginary
ImaginaryNumber operator - (RationalNumber lhs, ImaginaryNumber rhs)
{
	ImaginaryNumber res(rhs);

	if (lhs.is_float)
		res.real_part = RationalNumber(lhs.float_value) - rhs.real_part;
	else
		res.real_part = RationalNumber(lhs.int_value) - rhs.real_part;
	return res;
}

// rational * imaginary
ImaginaryNumber operator * (RationalNumber lhs, ImaginaryNumber rhs)
{
	ImaginaryNumber res(rhs);

	if (lhs.is_float)
	{
		res.real_part = RationalNumber(lhs.float_value) * res.real_part;
		res.imaginary_part = RationalNumber(lhs.float_value) * res.imaginary_part;
	}
	else
	{
		res.real_part = RationalNumber(lhs.int_value) * res.real_part;
		res.imaginary_part = RationalNumber(lhs.int_value) * res.imaginary_part;
	}
	return res;
}

// rational / imaginary
ImaginaryNumber operator  / (RationalNumber lhs, ImaginaryNumber rhs)
{
	ImaginaryNumber res(rhs);

	if (lhs.is_float)
	{
		res.real_part = RationalNumber(lhs.float_value) / res.real_part;
		res.imaginary_part = RationalNumber(lhs.float_value) / res.imaginary_part;
	}
	else
	{
		res.real_part = RationalNumber(lhs.int_value) / res.real_part;
		res.imaginary_part = RationalNumber(lhs.int_value) / res.imaginary_part;
	}
	return res;
}
