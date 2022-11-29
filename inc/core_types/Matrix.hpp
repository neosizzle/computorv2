#ifndef __MATRIX__H__
#define __MATRIX__H__
#include "Base.hpp"
#include <vector>

class Matrix : public BaseAssignmentType
{
private:
	std::vector<std::vector<BaseAssignmentType *>>	matrix;
	int												num_rows;
	int												num_cols;

public:
	std::string toString();

	// operator shell functions
	BaseAssignmentType * add (BaseAssignmentType *rhs);
	BaseAssignmentType * sub (BaseAssignmentType *rhs);
	BaseAssignmentType * mult (BaseAssignmentType *rhs);
	BaseAssignmentType * div (BaseAssignmentType *rhs);
	BaseAssignmentType * mod (BaseAssignmentType *rhs);
	BaseAssignmentType * pow (BaseAssignmentType *rhs);

	// getter and setter
	std::vector<std::vector<BaseAssignmentType *>>	get_matrix();
	void	set_matrix(std::vector<std::vector<BaseAssignmentType *>> matrix);

	int get_num_rows();
	
	int	get_num_cols();

	// constructors
	~Matrix();
	Matrix(std::vector<std::vector<BaseAssignmentType *>>	matrix);
	Matrix(std::string str);
	Matrix(const Matrix &other);

	Matrix &operator=(const Matrix &other);
};



#endif  //!__MATRIX__H__