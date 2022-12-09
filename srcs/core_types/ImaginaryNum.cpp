#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "Matrix.hpp"
#include "mixed_operators.hpp"

ImaginaryNumber ImaginaryNumber::simplify(ImaginaryNumber num)
{
	int cycle;
	ImaginaryNumber res;

	cycle = num.power % 4;
	if (cycle == 1)
	{
		res.imaginary_part = num.imaginary_part;
		res.real_part = num.real_part;
		res.power = 1;
	}
	else if (cycle == 2)
	{
		res.imaginary_part = num.real_part - num.imaginary_part;
		res.power = 0;
		res.real_part = RationalNumber(0);
	}
	else if (cycle == 3)
	{
		res.imaginary_part = num.imaginary_part * RationalNumber(-1);
		res.real_part = num.real_part;
		res.power = 1;
	}
	else if (cycle == 0)
	{
		res.imaginary_part = num.real_part + num.imaginary_part;
		res.real_part = RationalNumber(0);
		res.power = 0;
	}
	return res;
}

std::string ImaginaryNumber::toString()
{
	int cycle;
	std::string res;

	cycle = this->power % 4;

	// a + bi
	if (cycle == 1)
	{
		if (real_part != RationalNumber(0))
			res.append(real_part.toString() + "+");
		res.append(imaginary_part.toString() + "i");
	}
	// a + b(-1) = a - b
	else if (cycle == 2)
	{
		RationalNumber res_nbr;

		res_nbr = this->real_part - this->imaginary_part;
		res.append(res_nbr.toString());
	}
	// a - bi
	else if (cycle == 3)
	{
		if (real_part != RationalNumber(0))
			res.append(real_part.toString());
		res.append("-" + imaginary_part.toString() + "i");
	}
	// a + b(1) = a + b
	else if (cycle == 0)
	{
		RationalNumber res_nbr;

		res_nbr = this->real_part + this->imaginary_part;
		res.append(res_nbr.toString());
	}
	return res;
}

// ADD TYPE 
BaseAssignmentType *ImaginaryNumber::add(BaseAssignmentType *rhs)
{
	if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		ImaginaryNumber res = *this + *(curr_token);
		return new ImaginaryNumber(res);
	}
	else if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		ImaginaryNumber res = *this + *(curr_token);
		return new ImaginaryNumber(res);
	}
	return nullptr;
}

BaseAssignmentType *ImaginaryNumber::sub(BaseAssignmentType *rhs)
{
	if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		ImaginaryNumber res = *this - *(curr_token);
		return new ImaginaryNumber(res);
	}
	else if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		ImaginaryNumber res = *this - *(curr_token);
		return new ImaginaryNumber(res);
	}
	return nullptr;
}

BaseAssignmentType *ImaginaryNumber::mult(BaseAssignmentType *rhs)
{
	if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		ImaginaryNumber res = *this * *(curr_token);
		return new ImaginaryNumber(res);
	}
	else if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
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

BaseAssignmentType *ImaginaryNumber::div(BaseAssignmentType *rhs)
{
	if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		ImaginaryNumber res = *this / *(curr_token);
		return new ImaginaryNumber(res);
	}
	else if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
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
BaseAssignmentType *ImaginaryNumber::mod(BaseAssignmentType *rhs)
{
	if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		ImaginaryNumber res = *this % *(curr_token);
		return new ImaginaryNumber(res);
	}
	return nullptr;
}

BaseAssignmentType *ImaginaryNumber::pow(BaseAssignmentType *rhs)
{
	if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		ImaginaryNumber res = *this ^ *(curr_token);
		return new ImaginaryNumber(res);
	}
	else if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		ImaginaryNumber res = *this ^ *(curr_token);
		return new ImaginaryNumber(res);
	}
	return nullptr;
}

ImaginaryNumber ImaginaryNumber::operator+(ImaginaryNumber rhs)
{
	ImaginaryNumber res;

	res.imaginary_part = rhs.imaginary_part + this->imaginary_part;
	res.real_part = rhs.real_part + this->real_part;

	return res;
}

ImaginaryNumber ImaginaryNumber::operator-(ImaginaryNumber rhs)
{
	ImaginaryNumber res;

	res.imaginary_part = this->imaginary_part - rhs.imaginary_part;
	res.real_part = this->real_part - rhs.real_part;
	return res;
}
ImaginaryNumber ImaginaryNumber::operator*(ImaginaryNumber rhs)
{
	ImaginaryNumber res;
	ImaginaryNumber lhs_simplified;
	ImaginaryNumber rhs_simplified;

	lhs_simplified = this->simplify(*this);
	rhs_simplified = this->simplify(rhs);

	if (lhs_simplified.power == 1 && rhs_simplified.power == 0)
	{
		res.real_part = lhs_simplified.real_part * rhs_simplified.imaginary_part;
		res.imaginary_part = lhs_simplified.imaginary_part * rhs_simplified.imaginary_part;
		res.power = 1;
	}
	else if (lhs_simplified.power == 0 && rhs_simplified.power == 1)
	{
		res.real_part = rhs_simplified.real_part * lhs_simplified.imaginary_part;
		res.imaginary_part = rhs_simplified.imaginary_part * lhs_simplified.imaginary_part;
		res.power = 1;
	}
	else if (lhs_simplified.power == 0 && rhs_simplified.power == 0)
	{
		rhs.imaginary_part = lhs_simplified.imaginary_part * rhs_simplified.imaginary_part;
		rhs.real_part = RationalNumber(0);
		rhs.power = 0;
	}
	else if (lhs_simplified.power == 1 && rhs_simplified.power == 1)
	{
		ImaginaryNumber base;
		ImaginaryNumber third_term;

		base.real_part = lhs_simplified.real_part * rhs_simplified.real_part;
		base.imaginary_part = (lhs_simplified.real_part * rhs_simplified.imaginary_part) + (rhs_simplified.real_part * lhs_simplified.imaginary_part);
		third_term.real_part = RationalNumber(0);
		third_term.imaginary_part = lhs_simplified.imaginary_part * rhs_simplified.imaginary_part;
		third_term.power = 2;
		third_term = this->simplify(third_term);
		if (third_term.power == 1)
			base.imaginary_part = base.imaginary_part + third_term.imaginary_part;
		else if (third_term.power == 0)
			base.real_part = base.real_part + third_term.imaginary_part;
		res = base;
	}
	return res;
}
ImaginaryNumber ImaginaryNumber::operator/(ImaginaryNumber rhs)
{
	ImaginaryNumber res;
	ImaginaryNumber lhs_simplified;
	ImaginaryNumber rhs_simplified;

	lhs_simplified = this->simplify(*this);
	rhs_simplified = this->simplify(rhs);

	if (rhs == *this)
	{
		res.real_part = 1;
		res.imaginary_part = 0;
		res.power = 0;
	}
	else if (lhs_simplified.power == 0 && rhs_simplified.power == 0)
	{
		res.real_part = 0;
		res.imaginary_part = lhs_simplified.imaginary_part / rhs_simplified.imaginary_part;
		res.power = 0;
	}
	else if (lhs_simplified.power == 1 && rhs_simplified.power == 0)
	{
		if (rhs_simplified.imaginary_part != 0)
		{
			res.real_part = lhs_simplified.real_part / rhs_simplified.imaginary_part;
			res.imaginary_part = lhs_simplified.imaginary_part / rhs_simplified.imaginary_part;
		}
		else if (rhs_simplified.real_part != 0)
		{
			res.real_part = lhs_simplified.real_part / rhs_simplified.real_part;
			res.imaginary_part = lhs_simplified.imaginary_part / rhs_simplified.real_part;
		}
		res.power = 1;
	}
	else if (lhs_simplified.power == 0 && rhs_simplified.power == 1 || lhs_simplified.power == 1 && rhs_simplified.power == 1)
	{
		ImaginaryNumber inverse(rhs_simplified);
		inverse.imaginary_part = inverse.imaginary_part * -1;

		lhs_simplified = this->simplify(lhs_simplified * inverse);
		rhs_simplified = this->simplify(rhs_simplified * inverse);

		// by now, rhs power i should be 0
		if (rhs_simplified.imaginary_part != 0)
		{
			res.real_part = lhs_simplified.real_part / rhs_simplified.imaginary_part;
			res.imaginary_part = lhs_simplified.imaginary_part / rhs_simplified.imaginary_part;
		}
		else if (rhs_simplified.real_part != 0)
		{
			res.real_part = lhs_simplified.real_part / rhs_simplified.real_part;
			res.imaginary_part = lhs_simplified.imaginary_part / rhs_simplified.real_part;
		}
		res.power = 1;
	}

	return res;
}
ImaginaryNumber ImaginaryNumber::operator%(ImaginaryNumber rhs)
{
	ImaginaryNumber res;

	res.imaginary_part = this->imaginary_part % rhs.imaginary_part;
	res.power = this->power - rhs.power;

	return res;
}
ImaginaryNumber ImaginaryNumber::operator^(ImaginaryNumber rhs)
{
	ImaginaryNumber res;

	res.imaginary_part = this->imaginary_part ^ rhs.imaginary_part;
	res.power = this->power + rhs.power;
	return res;
}
