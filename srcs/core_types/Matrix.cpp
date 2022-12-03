#include "Matrix.hpp"
#include "ft_error.hpp"
#include "constants.hpp"
#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"

int derive_token_type(std::string str);
std::vector<std::string> ft_split(std::string str, std::vector<std::string> delims);
BaseAssignmentType *clone_token(BaseAssignmentType * token);

void	free_tokens(std::vector<BaseAssignmentType *> tokens);

/**
 * Adds row to curr matrix
*/
void	Matrix::add_row(std::vector<BaseAssignmentType *> row)
{
	this->matrix.push_back(row);
}

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
BaseAssignmentType * Matrix::add(BaseAssignmentType *rhs){
	if (rhs->getType() == N_MATRIX)
	{
		std::cout << "hi1\n";
		Matrix *curr_token = dynamic_cast<Matrix *>(rhs);
		std::cout << "hi2\n";
		Matrix res = *this + *(curr_token);
		std::cout << "hi3\n";
		return new Matrix(res);
	}
	return nullptr;
}

BaseAssignmentType * Matrix::sub(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Matrix::mult(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Matrix::div(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Matrix::mod(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Matrix::pow(BaseAssignmentType *rhs){return nullptr;}

/**
 * MAth operators
*/
Matrix Matrix::operator+(const Matrix &rhs)
{
	Matrix	res;

	if ((this->num_rows != rhs.num_rows) || (this->num_cols != rhs.num_cols)) 
		throw Ft_error("Cannot perform operation on bad size");
	for (size_t i = 0; i < this->num_rows; i++)
	{
		std::vector<BaseAssignmentType *> row;
		for (size_t j = 0; j < this->num_cols; j++)
		{
			// TODO add err check here
			row.push_back(this->matrix[i][j]->add(rhs.matrix[i][j]));
		}
		res.add_row(row);
	}
	return res;
}

Matrix Matrix::operator-(const Matrix &rhs)
{
	return this->matrix;
}

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
	for (size_t i = 1; i < matrix.size(); ++i)
	{
		if (matrix[i].size() != matrix[i - 1].size())
			throw Ft_error("Invalid matrix to be set");
	}
	

	this->matrix = matrix;
	this->num_rows = matrix.size();
	if (matrix.size() > 0)
		this->num_cols = matrix[0].size();
	else
		this->num_cols = 0;
}

// constructors
Matrix::Matrix()
{
	this->num_cols = 0;
	this->num_cols = 0;
	this->type = N_MATRIX;
}

Matrix::Matrix(std::vector<std::vector<BaseAssignmentType *>>	matrix)
{
	this->set_matrix(matrix);
	this->type = N_MATRIX;
}

// TODO implement matrix parse
Matrix::Matrix(std::string str)
{
	std::vector<std::vector<BaseAssignmentType*>> res;
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
		BaseAssignmentType *token;
		
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

			// for now, only accept rational number and imaginary number
			if (type != N_RATIONAL && type != N_IMAGINARY) throw Ft_error("Matrix only accepts rational numbers");
			else if (type == N_RATIONAL) token = new RationalNumber(atoi(col_strs[col_idx].c_str()));
			else if (type == N_IMAGINARY) token = new ImaginaryNumber(atoi(col_strs[col_idx].c_str()));	

			row.push_back(token);
		}
		
		// add row to res
		res.push_back(row);
	}

	this->set_matrix(res);
	this->type = N_MATRIX;
}

Matrix::Matrix(const Matrix &other)
{
	Matrix res;

	// free curr matrix
	// for (size_t i = 0; i < this->matrix.size(); i++)
	// 	free_tokens(this->matrix[i]);

	// // reallocate new matric
	// for (size_t i = 0; i < other.matrix.size(); i++)
	// 	free_tokens(this->matrix[i]);

	this->set_matrix(other.matrix);
	this->type = N_MATRIX;
}

Matrix & Matrix::operator=(const Matrix &other)
{
	this->set_matrix(other.matrix);
	this->type = N_MATRIX;
	return *this;
}

Matrix::~Matrix()
{
	for (size_t i = 0; i < this->matrix.size(); i++)
		free_tokens(this->matrix[i]);
}