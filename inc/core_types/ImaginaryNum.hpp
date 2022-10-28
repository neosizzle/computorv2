#ifndef __IMAGINARYNUM__H__
#define __IMAGINARYNUM__H__
#include "Base.hpp"
#include "RationalNum.hpp"

// TODO: Add const to copy constructor parameters
class ImaginaryNumber : public BaseAssignmentType
{
public:
	RationalNumber imaginary_part;
	RationalNumber real_part;
	int power;

public:
	std::string toString()
	{
		std::string res = imaginary_part.toString() + "i";

		if (power > 1)
			res += (std::string("^") + std::to_string(power));
		return res;
	}

	// operators
	// ImaginaryNumber +ImaginaryNumber
	// ImaginaryNumber operator+(ImaginaryNumber rhs)
	// {
	// 	ImaginaryNumber res;

	// 	res.imaginary_part = rhs.imaginary_part + this->imaginary_part;

	// 	return res;
	// }

	// // ImaginaryNumber -ImaginaryNumber
	// ImaginaryNumber operator-(ImaginaryNumber rhs)
	// {
	// 	ImaginaryNumber res;

	// 	res.imaginary_part = this->imaginary_part - rhs.imaginary_part;
	// 	return res;
	// }

	// // ImaginaryNumber *ImaginaryNumber
	// ImaginaryNumber operator*(ImaginaryNumber rhs)
	// {
	// 	ImaginaryNumber res;

	// 	res.imaginary_part = rhs.imaginary_part * this->imaginary_part;
	// 	res.power = this->power + rhs.power;
	// 	return res;
	// }

	// // ImaginaryNumber /ImaginaryNumber
	// ImaginaryNumber operator/(ImaginaryNumber rhs)
	// {
	// 	ImaginaryNumber res;

	// 	res.imaginary_part = this->imaginary_part / rhs.imaginary_part;
	// 	res.power = this->power - rhs.power;

	// 	return res;
	// }

	// // ImaginaryNumber ^ImaginaryNumber
	// ImaginaryNumber operator^(ImaginaryNumber rhs)
	// {
	// 	ImaginaryNumber res;

	// 	res.imaginary_part = this->imaginary_part ^ rhs.imaginary_part;
	// 	res.power = this->power + rhs.power;
	// 	return res;
	// }

	// // comparison operators
	// bool operator>(ImaginaryNumber rhs) { return this->imaginary_part > rhs.imaginary_part; }
	// bool operator<(ImaginaryNumber rhs) { return this->imaginary_part < rhs.imaginary_part; }
	// bool operator>=(ImaginaryNumber rhs) { return this->imaginary_part >= rhs.imaginary_part; }
	// bool operator==(ImaginaryNumber rhs) { return this->imaginary_part == rhs.imaginary_part; }
	// bool operator!=(ImaginaryNumber rhs) { return this->imaginary_part != rhs.imaginary_part; }

	// constructors
	ImaginaryNumber()
	{
		this->imaginary_part = RationalNumber(1);
		this->power = 1;
		this->type = N_IMAGINARY;
	}

	ImaginaryNumber(float x)
	{
		this->imaginary_part = RationalNumber(x);
		this->power = 1;
		this->type = N_IMAGINARY;
	}

	ImaginaryNumber(ImaginaryNumber &other)
	{
		this->imaginary_part = other.imaginary_part;
		this->power = other.power;
	}

	// assignment operators
	ImaginaryNumber &operator=(const ImaginaryNumber &other)
	{
		this->imaginary_part = other.imaginary_part;
		this->power = other.power;
		return *this;
	}
};

// RationalNumber + Imaginary number

// RationalNumber - Imaginary number

// RationalNumber * Imaginary number

// RationalNumber / Imaginary number

// Imaginary number + RationalNumber

// Imaginary number - RationalNumber

// Imaginary number * RationalNumber

// Imaginary number / RationalNumber

#endif  //!__IMAGINARYNUM__H__