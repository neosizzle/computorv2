#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "Matrix.hpp"
#include "mixed_operators.hpp"
#include "ft_error.hpp"

std::string RationalNumber::toString()
{
	if (!this->is_float) return std::to_string(this->int_value);
	if (this->float_value - static_cast<int>(this->float_value) == 0) return std::to_string(static_cast<int>(this->float_value));

	std::string res = std::to_string(float_value);

	// trim trailing zeroes
	size_t index_to_trim = res.find_last_not_of("0");
	res.erase(index_to_trim + 1);

	// if last character is '.', remove it also
	if (res[res.size() - 1] == 0)
		res.erase(res.size() - 2);
	return res;
}

// ADD TYPE
BaseAssignmentType *RationalNumber::add(BaseAssignmentType *rhs)
{
	// RationalNumber + Rational Bumber
	if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		RationalNumber res = *this + *(curr_token);
		return new RationalNumber(res);
	}
	else if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		ImaginaryNumber res = (*this) + *(curr_token);
		return new ImaginaryNumber(res);
	}
	return nullptr;
}

BaseAssignmentType * RationalNumber::sub (BaseAssignmentType *rhs)
{
	// RationalNumber + Rational Bumber
	if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		RationalNumber res = *this - *(curr_token);
		return new RationalNumber(res);
	}
	else if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		ImaginaryNumber res = *this - *(curr_token);
		return new ImaginaryNumber(res);
	}
	return nullptr;
}

BaseAssignmentType * RationalNumber::mult (BaseAssignmentType *rhs)
{
	// RationalNumber + Rational Bumber
	if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		RationalNumber res = *this * *(curr_token);
		return new RationalNumber(res);
	}
	else if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		ImaginaryNumber res = *this * *(curr_token);
		return new ImaginaryNumber(res);
	}
	else if (rhs->getType() == N_MATRIX)
	{
		Matrix *curr_token = dynamic_cast<Matrix *>(rhs);
		Matrix res = *this * *(curr_token);
		return new Matrix(res);
	}
	return nullptr;
}

BaseAssignmentType * RationalNumber::div (BaseAssignmentType *rhs)
{
	// RationalNumber + Rational Bumber
	if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		RationalNumber res = *this / *(curr_token);
		return new RationalNumber(res);
	}
	else if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		ImaginaryNumber res = *this / *(curr_token);
		return new ImaginaryNumber(res);
	}
	else if (rhs->getType() == N_MATRIX)
	{
		Matrix *curr_token = dynamic_cast<Matrix *>(rhs);
		Matrix res = *this / *(curr_token);
		return new Matrix(res);
	}
	return nullptr;

}

BaseAssignmentType * RationalNumber::mod (BaseAssignmentType *rhs)
{
	// RationalNumber + Rational Bumber
	if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		RationalNumber res = *this % *(curr_token);
		return new RationalNumber(res);
	}
	return nullptr;
}

BaseAssignmentType * RationalNumber::pow (BaseAssignmentType *rhs)
{
	// RationalNumber + Rational Bumber
	if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		RationalNumber res = *this ^ *(curr_token);
		return new RationalNumber(res);
	}
	return nullptr;
}

BaseAssignmentType * RationalNumber::matmult (BaseAssignmentType *rhs)
{
	(void) rhs;
	return nullptr;
}

RationalNumber RationalNumber::operator+(const RationalNumber &rhs)
{
	RationalNumber res;

	res.is_float = this->is_float || rhs.is_float;
	res.int_value = this->int_value + rhs.int_value;
	res.float_value = this->float_value + rhs.float_value;
	return res;
}

RationalNumber RationalNumber::operator-(const RationalNumber &rhs)
{
	RationalNumber res;

	res.is_float = this->is_float || rhs.is_float;
	res.int_value = this->int_value - rhs.int_value;
	res.float_value = this->float_value - rhs.float_value;
	return res;
}

RationalNumber RationalNumber::operator*(const RationalNumber &rhs)
{
	RationalNumber res;

	res.is_float = this->is_float || rhs.is_float;
	res.int_value = this->int_value * rhs.int_value;
	res.float_value = this->float_value * rhs.float_value;
	return res;
}

RationalNumber RationalNumber::operator/(const RationalNumber &rhs)
{
	RationalNumber res;

	if (rhs.float_value == 0 && rhs.int_value == 0)
		throw Ft_error("RationalNumber::operator/: Division by 0"); 
	res.int_value = this->int_value / rhs.int_value;
	res.float_value = this->float_value / rhs.float_value;
	if (this->float_value != 0 && this->int_value % rhs.int_value == 0 &&
	!rhs.is_float && !this->is_float)
		res.is_float = this->is_float || rhs.is_float;
	else
		res.is_float = (res.float_value != 0);

	return res;
}

RationalNumber RationalNumber::operator%(const RationalNumber &rhs)
{
	RationalNumber res;

	res.is_float = this->is_float || rhs.is_float;
	res.int_value = this->int_value % rhs.int_value;
	res.float_value = this->int_value;
	return res;
}

RationalNumber RationalNumber::operator^(const RationalNumber &rhs)
{
	RationalNumber res;

	res.is_float = this->is_float || rhs.is_float;
	res.int_value = std::pow(this->int_value, rhs.int_value);
	res.float_value = powf(this->float_value, rhs.float_value);
	return res;
}
