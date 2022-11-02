#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "mixed_operators.hpp"

std::string RationalNumber::toString()
{
	return this->is_float ? std::to_string(float_value) : std::to_string(int_value);
}

BaseAssignmentType *RationalNumber::add(BaseAssignmentType *rhs)
{
	std::cout << "add hit\n";
	std::cout << "rhs->getType() " << std::to_string(rhs->getType()) << "\n";
	// RationalNumber + Rational Bumber
	if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		RationalNumber res = *this + *(curr_token);
		return new RationalNumber(res);
	}
	else if (rhs->getType() == N_IMAGINARY)
	{
		std::cout << "aasadasd\n";
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
	// else if (rhs->getType() == N_IMAGINARY)
	// {
	// 	ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
	// 	ImaginaryNumber res = *this - *(curr_token);
	// 	return new RationalNumber(res);
	// }
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
	// else if (rhs->getType() == N_IMAGINARY)
	// {
	// 	ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
	// 	ImaginaryNumber res = *this * *(curr_token);
	// 	return new RationalNumber(res);
	// }
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
	float divResult;

	res.int_value = this->int_value / rhs.int_value;
	res.float_value = this->float_value / rhs.float_value;
	if (this->int_value != 0 && rhs.int_value % this->int_value == 0 &&
	!rhs.is_float && !this->is_float)
		res.is_float = this->is_float || rhs.is_float;
	else
		res.is_float = true;

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
