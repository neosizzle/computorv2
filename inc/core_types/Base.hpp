#ifndef __BASE__H__
#define __BASE__H__
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
#endif  //!__BASE__H__