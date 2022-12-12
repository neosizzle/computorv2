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

	std::vector<std::vector<BaseAssignmentType *>> _clone_matrix(std::vector<std::vector<BaseAssignmentType *>> mat);
	BaseAssignmentType *_get_dot_product(Matrix lhs, Matrix rhs, int res_row, int res_col);
	Matrix				_get_minors(Matrix mt);
	Matrix				_get_matrix_exc_row_col(Matrix mt, int row, int col);
	Matrix				_term_to_term_mult(Matrix m);

public:
	std::string toString();

	// operator shell functions
	BaseAssignmentType * add (BaseAssignmentType *rhs);
	BaseAssignmentType * sub (BaseAssignmentType *rhs);
	BaseAssignmentType * mult (BaseAssignmentType *rhs);
	BaseAssignmentType * div (BaseAssignmentType *rhs);
	BaseAssignmentType * mod (BaseAssignmentType *rhs);
	BaseAssignmentType * pow (BaseAssignmentType *rhs);
	BaseAssignmentType * matmult (BaseAssignmentType *rhs);

	// getter and setter
	std::vector<std::vector<BaseAssignmentType *>>	get_matrix();
	std::vector<std::vector<BaseAssignmentType *>> &get_matrix_ref();
	void	set_matrix(std::vector<std::vector<BaseAssignmentType *>> matrix);

	int get_num_rows() const;
	void	add_row(std::vector<BaseAssignmentType *> row);


	int	get_num_cols() const;

	// math operators
	Matrix operator+(const Matrix &rhs);
	Matrix operator-(const Matrix &rhs);
	Matrix operator*(const Matrix &rhs);
	Matrix operator/( Matrix &rhs);

	// calculate determinant
	BaseAssignmentType *get_determinant(Matrix mat);

	// evaluate adjoint
	Matrix transpose_matrix(Matrix mt);

	// get inverse matrix (mallocs)
	Matrix *get_inverse_matrix(Matrix mt);

	// constructors
	~Matrix();
	Matrix();
	Matrix(std::vector<std::vector<BaseAssignmentType *>>	matrix);
	Matrix(std::string str);
	Matrix(const Matrix &other);

	Matrix &operator=(const Matrix &other);
};



#endif  //!__MATRIX__H__