#include "Matrix.hpp"
#include "ft_error.hpp"

int derive_token_type(std::string str);
std::vector<std::string> ft_split(std::string str, std::vector<std::string> delims);
/**
 * Converts matrix class to string
*/
std::string Matrix::toString()
{
	std::string res;

	for (size_t row = 0; row < this->matrix.size(); row++)
	{
		res.append("[");
		for (size_t col = 0; col < this->matrix[row].size(); col++)
		{
			res.append(" " + this->matrix[row][col]->toString() + " ");
			if (col + 1 !=  this->matrix[row].size())
				res.append(",");
		}
		res.append("]\n");
	}
	return res;
}

/**
 * TODO implement math
*/
BaseAssignmentType * Matrix::add(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Matrix::sub(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Matrix::mult(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Matrix::div(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Matrix::mod(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Matrix::pow(BaseAssignmentType *rhs){return nullptr;}

/**
 * Getter and setter
*/
int	Matrix::get_num_cols()
{
	return this->num_cols;
}

int Matrix::get_num_rows()
{
	return this->num_rows;
}

std::vector<std::vector<BaseAssignmentType *>>	Matrix::get_matrix()
{
	return this->matrix;
}

void	Matrix::set_matrix(std::vector<std::vector<BaseAssignmentType *>> matrix)
{
	// check if matrix is rectangular / square
	for (size_t i = 1; i < matrix.length(); ++i)
	{
		if (matrix[i].length() != matrix[i - 1].length())
			throw Ft_error("Invalid matrix to be set");
	}
	

	this->matrix = matrix;
	this->num_rows = matrix.length();
	if (matrix.length() > 0)
		this->num_cols = matrix.length[0].length();
	else
		this->num_cols = 0;
}

// constructors
Matrix::Matrix(std::vector<std::vector<BaseAssignmentType *>>	matrix)
{
	this->set_matrix(matrix);
}

// TODO implement matrix parse
Matrix::Matrix(std::string str)
{
	std::vector<std::vector<<BaseAssignmentType*>> res;
	std::vector<std::string> row_strs;
	int	row_idx;
	int	col_idx;

	row_idx = -1;

	//trim first and last brackets
	str.erase(0, 1);
	str.erase(str.size() - 1);

	// split the string into row strings by ';'
	row_strs = ft_split(str, {";"});

	// loop through rows
	while (++row_idx < row_strs.size())
	{
		std::vector<std::string> col_strs;
		std::vector<BaseAssignmentType *> row;
		std::string row_str;
		
		row_str = row_strs[row_idx];

		// trim first and last brackets
		row_str.erase(0, 1);
		row_str.erase(row_str.size() - 1);

		// generate columns
		col_strs = ft_split(row_str, {","});
		col_idx = -1;
		while (++col_idx < col_strs.size())
		{
			// generate token
			const int type = derive_token_type(col_strs[col_idx]);

			// for now, only accept rational number
			// if (type == )
		}
		

		// add row to res

		// increment row idx by row size
	}

	this->set_matrix res;
}

Matrix::Matrix(const Matrix &other)
{
	this->set_matrix(other.matrix);
}

Matrix & Matrix::operator=(const Matrix &other)
{
	this->set_matrix(other.matrix);
	return *this;
}