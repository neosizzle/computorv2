#ifndef __PARENTHESIS__H__
#define __PARENTHESIS__H__
#include "Base.hpp"
#include "constants.hpp"
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


#endif  //!__PARENTHESIS__H__