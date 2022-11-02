#ifndef __VARIABLE__H__
#define __VARIABLE__H__
#include "Base.hpp"
#include "constants.hpp"
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
		this->type = VAR;
	}

	// operator overloads
	Variable &operator=(const Variable &other)
	{
		this->name = other.name;
		this->type = VAR;
		return *this;
	}
};



#endif  //!__VARIABLE__H__