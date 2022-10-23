#ifndef __RATIONALNUM__H__
#define __RATIONALNUM__H__

#include "constants.hpp"
#include "Base.hpp"

class RationalNumber : public BaseAssignmentType
{
public:
	bool is_float;
	int int_value;
	float float_value;

	std::string toString()
	{
		return is_float ? std::to_string(float_value) : std::to_string(int_value);
	}

	// operators
	// RationalNumber + RationalNumber
	RationalNumber operator+(RationalNumber rhs)
	{
		RationalNumber res;

		res.is_float = this->is_float || rhs.is_float;
		res.int_value = this->int_value + rhs.int_value;
		res.float_value = this->float_value + rhs.float_value;
		return res;
	}

	// RationalNumber - RationalNumber
	RationalNumber operator-(RationalNumber rhs)
	{
		RationalNumber res;

		res.is_float = this->is_float || rhs.is_float;
		res.int_value = this->int_value - rhs.int_value;
		res.float_value = this->float_value - rhs.float_value;
		return res;
	}

	// RationalNumber * RationalNumber
	RationalNumber operator*(RationalNumber rhs)
	{
		RationalNumber res;

		res.is_float = this->is_float || rhs.is_float;
		res.int_value = this->int_value * rhs.int_value;
		res.float_value = this->float_value * rhs.float_value;
		return res;
	}

	// RationalNumber / RationalNumber
	RationalNumber operator/(RationalNumber rhs)
	{
		RationalNumber res;
		float divResult;

		res.int_value = this->int_value / rhs.int_value;
		res.float_value = this->float_value / rhs.float_value;
		if (rhs.int_value % this->int_value == 0 && !rhs.is_float && !this->is_float)
			res.is_float = this->is_float || rhs.is_float;
		else
			res.is_float = true;

		return res;
	}

	// RationalNumber % RationalNumber
	RationalNumber operator%(RationalNumber rhs)
	{
		RationalNumber res;

		res.is_float = this->is_float || rhs.is_float;
		res.int_value = this->int_value % rhs.int_value;
		res.float_value = this->int_value;
		return res;
	}

	// RationalNumber ^ RationalNumber
	RationalNumber operator^(RationalNumber rhs)
	{
		RationalNumber res;

		res.is_float = this->is_float || rhs.is_float;
		res.int_value = this->int_value % rhs.int_value;
		res.float_value = this->int_value;
		return res;
	}

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

	RationalNumber(RationalNumber &other)
	{
		this->is_float = other.is_float;
		this->int_value = other.int_value;
		this->float_value = other.float_value;
		this->type = other.type;
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