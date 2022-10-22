#ifndef __QMARK__H__
#define __QMARK__H__

#include "Base.hpp"
#include "constants.hpp"

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


#endif  //!__QMARK__H__