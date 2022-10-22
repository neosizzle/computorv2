#ifndef __OPERATOR__H__
#define __OPERATOR__H__

#include "Base.hpp"
#include "constants.hpp"

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


#endif  //!__OPERATOR__H__