#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "ft_error.hpp"
#include "Matrix.hpp"

void free_token(BaseAssignmentType * token);
void	ft_perror(Ft_error e);

/**
 * @brief Additional operators for matrix
 * 
 */

// matrix * rational
Matrix operator * (Matrix lhs, RationalNumber rhs)
{
	const std::vector<std::vector<BaseAssignmentType *>> matrix = lhs.get_matrix();

	std::vector<std::vector<BaseAssignmentType *>> matrix_res;
	for (int i = 0; i < lhs.get_num_rows(); ++i)
	{
		std::vector<BaseAssignmentType *> row;

		for (int j = 0; j < lhs.get_num_cols(); j++)
		{
			BaseAssignmentType *res_term = matrix[i][j]->mult(&rhs);
			if (res_term == nullptr) throw Ft_error("Invalid operation");
		
			row.push_back(res_term);
		}
		matrix_res.push_back(row);
	}
	return Matrix(matrix_res);
}

// matrix * imaginary
Matrix operator * (Matrix lhs, ImaginaryNumber rhs)
{
	const std::vector<std::vector<BaseAssignmentType *>> matrix = lhs.get_matrix();

	std::vector<std::vector<BaseAssignmentType *>> matrix_res;
	for (int i = 0; i < lhs.get_num_rows(); ++i)
	{
		std::vector<BaseAssignmentType *> row;

		for (int j = 0; j < lhs.get_num_cols(); j++)
		{
			BaseAssignmentType *res_term = matrix[i][j]->mult(&rhs);
			if (res_term == nullptr) throw Ft_error("Invalid operation");
		
			row.push_back(res_term);
		}
		matrix_res.push_back(row);
	}
	return Matrix(matrix_res);
}

// matrix / rational
Matrix operator / (Matrix lhs, RationalNumber rhs)
{
	const std::vector<std::vector<BaseAssignmentType *>> matrix = lhs.get_matrix();

	std::vector<std::vector<BaseAssignmentType *>> matrix_res;
	for (int i = 0; i < lhs.get_num_rows(); ++i)
	{
		std::vector<BaseAssignmentType *> row;

		for (int j = 0; j < lhs.get_num_cols(); j++)
		{
			BaseAssignmentType *res_term = matrix[i][j]->div(&rhs);
			if (res_term == nullptr) throw Ft_error("Invalid operation");
		
			row.push_back(res_term);
		}
		matrix_res.push_back(row);
	}
	return Matrix(matrix_res);
}

// matrix / imaginary
Matrix operator / (Matrix lhs, ImaginaryNumber rhs)
{
	const std::vector<std::vector<BaseAssignmentType *>> matrix = lhs.get_matrix();

	std::vector<std::vector<BaseAssignmentType *>> matrix_res;
	for (int i = 0; i < lhs.get_num_rows(); ++i)
	{
		std::vector<BaseAssignmentType *> row;

		for (int j = 0; j < lhs.get_num_cols(); j++)
		{
			BaseAssignmentType *res_term = matrix[i][j]->div(&rhs);
			if (res_term == nullptr) throw Ft_error("Invalid operation");
		
			row.push_back(res_term);
		}
		matrix_res.push_back(row);
	}
	return Matrix(matrix_res);
}