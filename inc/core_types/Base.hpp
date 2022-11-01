#ifndef __BASE__H__
#define __BASE__H__
#include <iostream>

class BaseAssignmentType
{
public:
	virtual std::string toString() = 0;

protected:
	int type;

public:
	int getType() { return this->type; }

	virtual BaseAssignmentType * add(BaseAssignmentType *rhs){return nullptr;}
	virtual BaseAssignmentType * sub(BaseAssignmentType *rhs){return nullptr;}
	virtual BaseAssignmentType * mult(BaseAssignmentType *rhs){return nullptr;}
	virtual BaseAssignmentType * div(BaseAssignmentType *rhs){return nullptr;}
	virtual BaseAssignmentType * mod(BaseAssignmentType *rhs){return nullptr;}
	virtual BaseAssignmentType * pow(BaseAssignmentType *rhs){return nullptr;}
	virtual BaseAssignmentType * matmult(BaseAssignmentType *rhs){return nullptr;}

};
#endif  //!__BASE__H__