#ifndef __ASSIGNMENTTYPES__H__
#define __ASSIGNMENTTYPES__H__
#include "libraries.hpp"

class BaseAssignmentType
{
public:
	virtual std::string toString() = 0;

protected:
	int type;

public:
	int getType() { return this->type; }
};

/////////////////
// MISC TYPES ///
/////////////////
class Operator : public BaseAssignmentType
{
private:
	std::string value;

public:
	std::string toString() { return value; }

	// constructors
	Operator(std::string value)
	{
		std::map<std::string, int>::const_iterator found = OPERATORS_MAP.find(value);

		this->value = value;
		this->type = found != OPERATORS_MAP.end() ? found->second : -1;
	}

	Operator(Operator &other)
	{
		this->value = other.value;
		this->type = other.type;
	}

	// operator overload
	Operator &operator=(const Operator &other)
	{
		this->value = other.value;
		this->type = other.type;
		return *this;
	}
};

class Parenthesis : public BaseAssignmentType
{
public:
	std::string toString()
	{
		return this->type == L_PARENTHESIS ? std::string("(") : std::string(")");
	}

public:
	// constructors
	Parenthesis(std::string symbol)
	{
		if (symbol == "(")
			this->type = L_PARENTHESIS;
		else
			this->type = R_PARENTHESIS;
	}

	Parenthesis(Parenthesis &other)
	{
		this->type = other.type;
	}

	// operator overloads
	Parenthesis &operator=(const Parenthesis &other)
	{
		this->type = other.type;
		return *this;
	}
};

class Variable : public BaseAssignmentType
{
public:
	std::string name;

	std::string toString() { return this->name; }

	// constructors
	Variable()
	{
		this->name = "";
		this->type = VAR;
	}

	Variable(std::string name)
	{
		this->name = name;
		this->type = VAR;
	}

	Variable(Variable &other)
	{
		this->name = other.name;
	}

	// operator overloads
	Variable &operator=(const Variable &other)
	{
		this->name = other.name;
		return *this;
	}
};


class QMark : public BaseAssignmentType
{
public:
	std::string toString()
	{
		return "?";
	}

public:
	// constructors
	QMark()
	{
		this->type = Q_MARK;
	}

	QMark(QMark &other)
	{
		this->type = other.type;
	}

	// operator overloads
	QMark &operator=(const QMark &other)
	{
		this->type = other.type;
		return *this;
	}
};

/////////////////
// CORE TYPES ///
/////////////////

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

class ImaginaryNumber : public BaseAssignmentType
{
public:
	RationalNumber imaginary_part;
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
	ImaginaryNumber operator+(ImaginaryNumber rhs)
	{
		ImaginaryNumber res;

		res.imaginary_part = rhs.imaginary_part + this->imaginary_part;

		return res;
	}

	// ImaginaryNumber -ImaginaryNumber
	ImaginaryNumber operator-(ImaginaryNumber rhs)
	{
		ImaginaryNumber res;

		res.imaginary_part = this->imaginary_part - rhs.imaginary_part;
		return res;
	}

	// ImaginaryNumber *ImaginaryNumber
	ImaginaryNumber operator*(ImaginaryNumber rhs)
	{
		ImaginaryNumber res;

		res.imaginary_part = rhs.imaginary_part * this->imaginary_part;
		res.power = this->power + rhs.power;
		return res;
	}

	// ImaginaryNumber /ImaginaryNumber
	ImaginaryNumber operator/(ImaginaryNumber rhs)
	{
		ImaginaryNumber res;

		res.imaginary_part = this->imaginary_part / rhs.imaginary_part;
		res.power = this->power - rhs.power;

		return res;
	}

	// ImaginaryNumber ^ImaginaryNumber
	ImaginaryNumber operator^(ImaginaryNumber rhs)
	{
		ImaginaryNumber res;

		res.imaginary_part = this->imaginary_part ^ rhs.imaginary_part;
		res.power = this->power + rhs.power;
		return res;
	}

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
#endif  //!__ASSIGNMENTTYPES__H__
