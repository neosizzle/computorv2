#ifndef __RATIONALNUM__H__
#define __RATIONALNUM__H__
#include "constants.hpp"
#include "Base.hpp"
#include <cmath>

class RationalNumber : public BaseAssignmentType
{
public:
	bool is_float;
	int int_value;
	float float_value;

	std::string toString();

	// ADD TYPE
	// operator shell functions
	BaseAssignmentType * add (BaseAssignmentType *rhs);
	BaseAssignmentType * sub (BaseAssignmentType *rhs);
	BaseAssignmentType * mult (BaseAssignmentType *rhs);
	BaseAssignmentType * div (BaseAssignmentType *rhs);
	BaseAssignmentType * mod (BaseAssignmentType *rhs);
	BaseAssignmentType * pow (BaseAssignmentType *rhs);

	// operators
	// RationalNumber + RationalNumber
	RationalNumber operator+(const RationalNumber &rhs);

	// RationalNumber - RationalNumber
	RationalNumber operator-(const RationalNumber &rhs);

	// RationalNumber * RationalNumber
	RationalNumber operator*(const RationalNumber &rhs);

	// RationalNumber / RationalNumber
	RationalNumber operator/(const RationalNumber &rhs);

	// RationalNumber % RationalNumber
	RationalNumber operator%(const RationalNumber &rhs);

	// RationalNumber ^ RationalNumber
	RationalNumber operator^(const RationalNumber &rhs);

	// comparison operators
	bool operator>(RationalNumber rhs) { return this->float_value > rhs.float_value; }
	bool operator<(RationalNumber rhs) { return this->float_value < rhs.float_value; }
	bool operator>=(RationalNumber rhs) { return this->float_value >= rhs.float_value; }
	bool operator==(RationalNumber rhs) { return this->float_value == rhs.float_value; }
	bool operator!=(RationalNumber rhs) { return this->float_value != rhs.float_value; }

	// constructors
	RationalNumber()
	{
		this->is_float = false;
		this->int_value = 0;
		this->float_value = 0;
		this->type = N_RATIONAL;
	}

	RationalNumber(int x)
	{
		this->is_float = false;
		this->int_value = x;
		this->float_value = x;
		this->type = N_RATIONAL;
	}

	RationalNumber(float x)
	{
		this->is_float = true;
		this->int_value = x;
		this->float_value = x;
		this->type = N_RATIONAL;
	}

	RationalNumber(const RationalNumber &other)
	{
		this->is_float = other.is_float;
		this->int_value = other.int_value;
		this->float_value = other.float_value;
		this->type = other.type;
	}
	
	RationalNumber(const RationalNumber *other)
	{
		this->is_float = other->is_float;
		this->int_value = other->int_value;
		this->float_value = other->float_value;
		this->type = other->type;
	}

	// assignment operators
	RationalNumber &operator=(const RationalNumber &other)
	{
		this->is_float = other.is_float;
		this->int_value = other.int_value;
		this->float_value = other.float_value;
		return *this;
	}
};

#endif  //!__RATIONALNUM__H__