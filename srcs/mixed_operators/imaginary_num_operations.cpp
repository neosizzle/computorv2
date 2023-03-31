#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "Matrix.hpp"
#include "ft_error.hpp"

/**
 * @brief Additional operators for Imaginary numbers
 * 
 */

// imaginary + rational
ImaginaryNumber operator + (ImaginaryNumber lhs, RationalNumber rhs)
{
	ImaginaryNumber res(lhs);

	if (rhs.is_float)
		res.real_part = lhs.real_part + RationalNumber(rhs.float_value);
	else
		res.real_part = lhs.real_part + RationalNumber(rhs.int_value);
	return res;
}


// imaginary - rational
ImaginaryNumber operator - (ImaginaryNumber lhs, RationalNumber rhs)
{
	ImaginaryNumber res(lhs);

	if (rhs.is_float)
		res.real_part = lhs.real_part - RationalNumber(rhs.float_value);
	else
		res.real_part = lhs.real_part - RationalNumber(rhs.int_value);
	return res;
}


// imaginary * rational
ImaginaryNumber operator * (ImaginaryNumber lhs, RationalNumber rhs)
{
	ImaginaryNumber res(lhs);

	if (rhs.is_float)
		res.real_part = lhs.real_part * RationalNumber(rhs.float_value);
	else
		res.real_part = lhs.real_part * RationalNumber(rhs.int_value);
	return res;
}


// imaginary / rational
ImaginaryNumber operator / (ImaginaryNumber lhs, RationalNumber rhs)
{
	ImaginaryNumber res(lhs);

	if (rhs.is_float)
		res.real_part = lhs.real_part / RationalNumber(rhs.float_value);
	else
		res.real_part = lhs.real_part / RationalNumber(rhs.int_value);
	return res;
}


// imaginary ^ rational
ImaginaryNumber operator ^ (ImaginaryNumber lhs, RationalNumber rhs)
{
	ImaginaryNumber res(lhs);
	RationalNumber newPower = RationalNumber(lhs.power) + rhs;

	if (rhs.is_float)
		res.real_part = lhs.real_part ^ RationalNumber(rhs.float_value);
	else
		res.real_part = lhs.real_part ^ RationalNumber(rhs.int_value);
	
	if (newPower.is_float)
		res.power = newPower.float_value;
	else
		res.power = newPower.int_value;
	return res;
}

// imaginary * matrix
Matrix operator * (ImaginaryNumber lhs, Matrix rhs)
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

// imaginary / matrix
Matrix operator / (ImaginaryNumber lhs, Matrix rhs)
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