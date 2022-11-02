#ifndef __IMAGINARYNUM__H__
#define __IMAGINARYNUM__H__
#include "Base.hpp"

class RationalNumber;
class ImaginaryNumber : public BaseAssignmentType
{
public:
	RationalNumber imaginary_part;
	RationalNumber real_part;
	int power;

private:
	ImaginaryNumber simplify(ImaginaryNumber num);


public:

	std::string toString();

	// operator shell functions
	BaseAssignmentType * add (BaseAssignmentType *rhs);
	BaseAssignmentType * sub (BaseAssignmentType *rhs);
	BaseAssignmentType * mult (BaseAssignmentType *rhs);
	BaseAssignmentType * div (BaseAssignmentType *rhs);
	BaseAssignmentType * mod (BaseAssignmentType *rhs);
	BaseAssignmentType * pow (BaseAssignmentType *rhs);

	// operators
	// ImaginaryNumber +ImaginaryNumber
	ImaginaryNumber operator+(ImaginaryNumber rhs);
	// ImaginaryNumber -ImaginaryNumber
	ImaginaryNumber operator-(ImaginaryNumber rhs);

	// ImaginaryNumber *ImaginaryNumber
	ImaginaryNumber operator*(ImaginaryNumber rhs);

	// ImaginaryNumber /ImaginaryNumber
	ImaginaryNumber operator/(ImaginaryNumber rhs);

	// ImaginaryNumber % ImaginaryNumber
	ImaginaryNumber operator%(ImaginaryNumber rhs);

	// ImaginaryNumber ^ImaginaryNumber
	ImaginaryNumber operator^(ImaginaryNumber rhs);

	// comparison operators
	bool operator>(ImaginaryNumber rhs) { return this->imaginary_part > rhs.imaginary_part; }
	bool operator<(ImaginaryNumber rhs) { return this->imaginary_part < rhs.imaginary_part; }
	bool operator>=(ImaginaryNumber rhs) { return this->imaginary_part >= rhs.imaginary_part; }
	bool operator==(ImaginaryNumber rhs) { return this->imaginary_part == rhs.imaginary_part; }
	bool operator!=(ImaginaryNumber rhs) { return this->imaginary_part != rhs.imaginary_part; }

	// constructors
	ImaginaryNumber()
	{
		this->imaginary_part = RationalNumber(1);
		this->real_part = RationalNumber(0);
		this->power = 1;
		this->type = N_IMAGINARY;
	}

	ImaginaryNumber(const RationalNumber &x)
	{
		this->imaginary_part = x;
		this->real_part = RationalNumber(0);
		this->power = 1;
		this->type = N_IMAGINARY;
	}

	ImaginaryNumber(const RationalNumber &x, int power)
	{
		this->imaginary_part = x;
		this->real_part = RationalNumber(0);
		this->power = power;
		this->type = N_IMAGINARY;
	}


	ImaginaryNumber(const ImaginaryNumber &other)
	{
		this->imaginary_part = other.imaginary_part;
		this->real_part = other.real_part;
		this->power = other.power;
		this->type = N_IMAGINARY;
	}


	// assignment operators
	ImaginaryNumber &operator=(const ImaginaryNumber &other)
	{
		this->imaginary_part = other.imaginary_part;
		this->real_part = other.real_part;
		this->power = other.power;
		this->type = N_IMAGINARY;
		return *this;
	}
};

#endif  //!__IMAGINARYNUM__H__