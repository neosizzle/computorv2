#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "ft_error.hpp"
#include "Matrix.hpp"


void free_token(BaseAssignmentType * token);
void	ft_perror(Ft_error e);
/**
 * @brief Additional operators for rational numbers
 * 
 */

// rational + imaginary
ImaginaryNumber operator + (RationalNumber lhs, ImaginaryNumber rhs)
{
	ImaginaryNumber res(rhs);

	if (lhs.is_float)
		res.real_part = rhs.real_part + RationalNumber(lhs.float_value);
	else
		res.real_part = rhs.real_part + RationalNumber(lhs.int_value);
	return res;
}

// rational - imaginary
ImaginaryNumber operator - (RationalNumber lhs, ImaginaryNumber rhs)
{
	ImaginaryNumber res(rhs);

	if (lhs.is_float)
		res.real_part = RationalNumber(lhs.float_value) - rhs.real_part;
	else
		res.real_part = RationalNumber(lhs.int_value) - rhs.real_part;
	return res;
}

// rational * imaginary
ImaginaryNumber operator * (RationalNumber lhs, ImaginaryNumber rhs)
{
	ImaginaryNumber res(rhs);

	if (lhs.is_float)
	{
		res.real_part = RationalNumber(lhs.float_value) * res.real_part;
		res.imaginary_part = RationalNumber(lhs.float_value) * res.imaginary_part;
	}
	else
	{
		res.real_part = RationalNumber(lhs.int_value) * res.real_part;
		res.imaginary_part = RationalNumber(lhs.int_value) * res.imaginary_part;
	}
	return res;
}

// rational / imaginary
ImaginaryNumber operator  / (RationalNumber lhs, ImaginaryNumber rhs)
{
	ImaginaryNumber res(rhs);

	if (lhs.is_float)
	{
		res.real_part = RationalNumber(lhs.float_value) / res.real_part;
		res.imaginary_part = RationalNumber(lhs.float_value) / res.imaginary_part;
	}
	else
	{
		res.real_part = RationalNumber(lhs.int_value) / res.real_part;
		res.imaginary_part = RationalNumber(lhs.int_value) / res.imaginary_part;
	}
	return res;
}

// rational * matrix
Matrix operator * (RationalNumber lhs, Matrix rhs)
{
	const std::vector<std::vector<BaseAssignmentType *>> matrix = rhs.get_matrix();

	std::vector<std::vector<BaseAssignmentType *>> matrix_res;
	for (size_t i = 0; i < rhs.get_num_rows(); ++i)
	{
		std::vector<BaseAssignmentType *> row;

		for (size_t j = 0; j < rhs.get_num_cols(); j++)
		{
			BaseAssignmentType *res_term = lhs.mult(matrix[i][j]);
			if (res_term == nullptr) throw Ft_error("Invalid operation");
		
			row.push_back(res_term);
		}
		matrix_res.push_back(row);
	}
	return Matrix(matrix_res);
}

// rational / matrix
Matrix operator / (RationalNumber lhs, Matrix rhs)
{
	Matrix *inverse;
	Matrix *res_ptr;

	inverse = rhs.get_inverse_matrix(rhs);
	res_ptr = dynamic_cast<Matrix *>(lhs.mult(inverse));
	Matrix res((*res_ptr));
	delete inverse;
	delete res_ptr;
	return res;
}