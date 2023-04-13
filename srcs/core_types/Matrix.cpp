#include "Matrix.hpp"
#include "ft_error.hpp"
#include "constants.hpp"
#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include <algorithm>
#include "mixed_operators.hpp"

int derive_token_type(std::string str);
std::vector<std::string> ft_split(std::string str, std::vector<std::string> delims);
BaseAssignmentType *clone_token(BaseAssignmentType * token);
void	free_tokens(std::vector<BaseAssignmentType *> tokens);
void free_token(BaseAssignmentType * token);
void	ft_perror(Ft_error err);

/**
 * Adds row to curr matrix
*/
void	Matrix::add_row(std::vector<BaseAssignmentType *> row)
{
	if (this->num_cols != 0 && row.size() != std::size_t(this->num_cols))
		throw Ft_error("Matrix::add_row: Invalid row to add");
	this->matrix.push_back(row);
	++this->num_rows;
	this->num_cols = row.size();
}

/**
 * clones matrix object
*/
std::vector<std::vector<BaseAssignmentType *>> Matrix::_clone_matrix(std::vector<std::vector<BaseAssignmentType *>> mat)
{
	std::vector<std::vector<BaseAssignmentType *>> res;

	for (size_t i = 0; i < mat.size(); i++)
	{
		std::vector<BaseAssignmentType *> row;

		for (size_t j = 0; j < mat[i].size(); j++)
		{
			row.push_back(clone_token(mat[i][j]));
		}
		res.push_back(row);
	}
	return res;
}

/**
 * Gets term to term product of matrix with curr matrix
*/
Matrix Matrix::_term_to_term_mult(Matrix m)
{
	Matrix res;

	// throw err if dimensions different
	if ((m.get_num_cols() != this->num_cols) || (m.get_num_rows() != this->num_rows))
		throw Ft_error("Matrix::_term_to_term_mult Expecting equal dimension matrix");

	for (int row_num = 0; row_num < m.get_num_rows(); row_num++)
	{
		std::vector<BaseAssignmentType *> row;
		for (int col_num = 0; col_num < m.get_num_cols(); col_num++)
		{
			BaseAssignmentType *curr_term;

			curr_term = this->matrix[row_num][col_num]->mult(m.get_matrix()[row_num][col_num]);
			row.push_back(curr_term);
		}
		
		res.add_row(row);
	}
	return res;
}

/**
 * Gets dot product of matrix at current row and curr col (Mallocs)
*/
BaseAssignmentType * Matrix::_get_dot_product(Matrix lhs, Matrix rhs, int res_row, int res_col)
{
	BaseAssignmentType *res;
	BaseAssignmentType *temp;
	
	// if lhs column num != rhs row num, throw err
	if (lhs.get_num_cols() != rhs.get_num_rows()) throw Ft_error("Invalid matrix for dot product");

	// initiaize res
	res = new RationalNumber(0);

	// loop through each column of lhs at res_row
	for (int i = 0; i < lhs.get_num_cols(); i++)
	{
		BaseAssignmentType *curr_num_lhs = lhs.matrix[res_row][i];
		BaseAssignmentType *curr_num_rhs = rhs.matrix[i][res_col];
		BaseAssignmentType *curr_num_res = curr_num_lhs->mult(curr_num_rhs);

		temp = clone_token(res);
		free_token(res);
		res = temp->add(curr_num_res);
		free_token(temp);
		free_token(curr_num_res);
	}
	return res;
}

/**
 * Calculate determinant of a matrix (Mallocs)
*/
BaseAssignmentType * Matrix::get_determinant(Matrix mat)
{
	BaseAssignmentType *res;
	BaseAssignmentType *curr_determ_res;
	BaseAssignmentType *aux;
	BaseAssignmentType *temp;

	// if matrix is not square, throw error
	if (mat.get_num_cols() != mat.get_num_rows()) throw Ft_error("Expected square matrix");

	res = new RationalNumber(0);

	// base case, matrix is 2x2	
	if (mat.get_num_cols() == 2 && mat.get_num_rows() == 2)
	{
		aux = res;
		res = (mat.matrix[0][0]->mult(mat.matrix[1][1]));
		free_token(aux);
		aux = res;
		temp = (mat.matrix[0][1]->mult(mat.matrix[1][0]));
		res = res->sub(temp);
		free_token(temp);
		free_token(aux);
		return res;
	}

	// another base case, matrix is 1x1
	if (mat.get_num_cols() == 1 && mat.get_num_rows() == 1)
	{
		free_token(res);
		res = clone_token(mat.matrix[0][0]);
		return res;
	}

	// for every col in first list
	for (int first_row_col = 0; first_row_col < mat.get_num_cols(); first_row_col++)
	{
		// form another matrix w/o row and col
		Matrix child;
		for (int child_row_num = 1; child_row_num < mat.get_num_rows(); child_row_num++)
		{
			std::vector<BaseAssignmentType *> child_row;

			for (int child_col = 0; child_col < mat.get_num_cols(); child_col++)
			{
				// if current child col is equal to first row col, continue
				if (child_col == first_row_col) continue ;

				// push the current element to row
				child_row.push_back(clone_token(mat.matrix[child_row_num][child_col]));
			}
			
			// push row to child matrix
			child.add_row(child_row);
		}
		
		// assign current determinant result into curr_num * get_determ(new_mat)
		temp = this->get_determinant(child);
		curr_determ_res = mat.matrix[0][first_row_col]->mult(temp);

		// plus or minus result based on curr idx orr or even
		aux = res;
		if (first_row_col % 2 == 0)
			res = res->add(curr_determ_res);
		else
			res = res->sub(curr_determ_res);
		free_token(curr_determ_res);
		free_token(aux);
		free_token(temp);
	}
	return res;
}

/**
 * Form matrix w/o row and col
*/
Matrix	Matrix::_get_matrix_exc_row_col(Matrix mtx, int row, int col)
{
	Matrix res;
	int		curr_row;
	int		curr_col;

	curr_row = -1;
	while (++curr_row < mtx.get_num_rows())
	{
		// continue if current row matches row to exclude
		if (curr_row == row) continue;

		std::vector<BaseAssignmentType *> row;
		curr_col = -1;
		while (++curr_col < mtx.get_num_cols())
		{
			// continue if current col matchs col to exclude
			if (curr_col == col) continue;
			row.push_back(clone_token(mtx.get_matrix()[curr_row][curr_col]));
		}
		res.add_row(row);
	}

	return res;
}

/**
 * Get minor matrix
*/
Matrix Matrix::_get_minors(Matrix mtx)
{
	Matrix res;
	int curr_mtx_row;
	int	curr_mtx_col;

	curr_mtx_row = -1;

	// for every element
	while (++curr_mtx_row < mtx.get_num_rows())
	{
		std::vector<BaseAssignmentType *> row;

		curr_mtx_col = -1;
		while (++curr_mtx_col < mtx.get_num_cols())
		{
			// Matrix test = this->_get_matrix_exc_row_col(mtx, curr_mtx_row, curr_mtx_col);
			// std::cout << test.toString() << "\n";

			// form matrix without curr row and col
			Matrix sub(this->_get_matrix_exc_row_col(mtx, curr_mtx_row, curr_mtx_col));
			
			// calculate determinant for new matrix
			BaseAssignmentType * determ = this->get_determinant(sub);

			// add res to matrix
			row.push_back(determ);
		}
		res.add_row(row);
	}

	return res;
}

/**
 * Calculate Adjoint matrix
*/
Matrix Matrix::transpose_matrix(Matrix mat)
{

	// throw error if not a square matrix
	if (mat.get_num_cols() != mat.get_num_rows()) throw Ft_error("Square matrix expected");

	// base case - mat has 1 row and 1 col
	if (mat.get_num_cols() == 1 && mat.get_num_rows() == 1)
		return mat;
	
	// create new matrix without 1st row and col of curr matrix
	Matrix child_matrix;

	//iterate from first row
	for (int child_mat_row = 1; child_mat_row < mat.get_num_rows(); child_mat_row++)
	{
		std::vector<BaseAssignmentType *> row;

		// iterator from first column
		for (int child_mat_col = 1; child_mat_col < mat.get_num_cols(); child_mat_col++)
			row.push_back(clone_token(mat.matrix[child_mat_row][child_mat_col]));
		child_matrix.add_row(row);
	}

	// call transpose matrix on new matrix
	Matrix child_transposed = this->transpose_matrix(child_matrix);

	// once return, apply new elements to input matrix's submatrix
	for (int child_mat_row = 0; child_mat_row < child_transposed.get_num_rows(); child_mat_row++)
	{
		// free here?
		for (int child_mat_col = 0; child_mat_col < child_transposed.get_num_cols(); child_mat_col++)
		{
			free_token(mat.matrix[child_mat_row + 1][child_mat_col + 1]);
			mat.matrix[child_mat_row + 1][child_mat_col + 1] = clone_token(child_transposed.matrix[child_mat_row][child_mat_col]); 
		}
	}
		

	// loop through first row and switch values with column
	for (int mat_row = 0; mat_row < mat.get_num_rows(); mat_row++)
	{
		BaseAssignmentType *temp;
		BaseAssignmentType *aux;

		temp = clone_token(mat.matrix[mat_row][0]);
		aux = mat.matrix[mat_row][0];
		mat.matrix[mat_row][0] = clone_token(mat.matrix[0][mat_row]);
		free_token(aux);
		aux = mat.matrix[0][mat_row];
		mat.matrix[0][mat_row] = temp;
		free_token(aux);
	}
	

	// return modified input matrix
	return mat;
}

/**
 * Calculate matrix inverse
*/
Matrix *Matrix::get_inverse_matrix(Matrix mt)
{
	Matrix res;
	Matrix curr_state;

	// get matrix of minors
	Matrix minors(this->_get_minors(mt));

	// get matrix of cofactors
	for (int row = 0; row < minors.get_num_rows(); row++)
	{
		for (int col = 0; col < minors.get_num_cols(); col++)
		{
			// (if row is even and col is odd) or (row is odd and col is even)
			if ((row % 2 == 0 && col % 2 != 0) || (row % 2 != 0 && col % 2 == 0))
			{
				BaseAssignmentType *temp;

				temp = minors.get_matrix()[row][col];

				// create new token
				RationalNumber neg_one(-1);
				BaseAssignmentType *new_val = temp->mult(&neg_one);


				// free old token
				free_token(temp);
				minors.get_matrix_ref()[row][col] = new_val;
			}
		}
		
	}
	

	// transpose matrix
	Matrix transposed(transpose_matrix(minors));

	// get determinant
	BaseAssignmentType *determinant = this->get_determinant(mt);

	// multiple 1/determinant with adjuvant
	RationalNumber one(1);
	BaseAssignmentType *determ_inverse = one.div(determinant);
	Matrix *result = dynamic_cast<Matrix *>(determ_inverse->mult(&transposed));

	// free intermidiary tokens
	free_token(determinant);
	free_token(determ_inverse);

	// return res
	return result;
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
			if (std::size_t(col + 1) !=  this->matrix[row].size())
				res.append(",");
		}
		res.append("]\n");
	}
	return res;
}

BaseAssignmentType * Matrix::add(BaseAssignmentType *rhs){
	if (rhs->getType() == N_MATRIX)
	{
		Matrix *curr_token = dynamic_cast<Matrix *>(rhs);
		Matrix res = *this + *(curr_token);
		return new Matrix(res);
	}
	return nullptr;
}

BaseAssignmentType * Matrix::sub(BaseAssignmentType *rhs){
	if (rhs->getType() == N_MATRIX)
	{
		Matrix *curr_token = dynamic_cast<Matrix *>(rhs);
		Matrix res = *this - *(curr_token);
		return new Matrix(res);
	}
	return nullptr;
}
BaseAssignmentType * Matrix::mult(BaseAssignmentType *rhs){
	if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		Matrix res = *this * *(curr_token);
		return new Matrix(res);
	}
	else if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		Matrix res = *this * *(curr_token);
		return new Matrix(res);
	}
	else if (rhs->getType() == N_MATRIX)
	{
		try
		{
			Matrix *curr_token = dynamic_cast<Matrix *>(rhs);
			Matrix res = this->_term_to_term_mult(*curr_token);
			return new Matrix(res);
		}
		catch(Ft_error e)
		{
			ft_perror(e);
			return nullptr;
		}
	}
	return nullptr;
}
BaseAssignmentType * Matrix::div(BaseAssignmentType *rhs){
	if (rhs->getType() == N_MATRIX)
	{
		Matrix *curr_token = dynamic_cast<Matrix *>(rhs);
		Matrix res = *this / *(curr_token);
		return new Matrix(res);
	}
	else if (rhs->getType() == N_RATIONAL)
	{
		RationalNumber *curr_token = dynamic_cast<RationalNumber *>(rhs);
		Matrix res = *this / *(curr_token);
		return new Matrix(res);
	}
	else if (rhs->getType() == N_IMAGINARY)
	{
		ImaginaryNumber *curr_token = dynamic_cast<ImaginaryNumber *>(rhs);
		Matrix res = *this / *(curr_token);
		return new Matrix(res);
	}
	return nullptr;
}
BaseAssignmentType * Matrix::mod(BaseAssignmentType *rhs){(void) rhs; return nullptr;}
BaseAssignmentType * Matrix::pow(BaseAssignmentType *rhs){(void) rhs; return nullptr;}

BaseAssignmentType * Matrix::matmult(BaseAssignmentType *rhs){
	if (rhs->getType() == N_MATRIX)
	{
		Matrix *curr_token = dynamic_cast<Matrix *>(rhs);
		Matrix res = *this * *(curr_token);
		return new Matrix(res);
	}
	return nullptr;
}

/**
 * MAth operators
*/
Matrix Matrix::operator+(const Matrix &rhs)
{
	Matrix	res;
	BaseAssignmentType *curr_res;

	if ((this->num_rows != rhs.num_rows) || (this->num_cols != rhs.num_cols)) 
		throw Ft_error("Cannot perform operation on bad size");
	for (int i = 0; i < this->num_rows; i++)
	{
		std::vector<BaseAssignmentType *> row;
		for (int j = 0; j < this->num_cols; j++)
		{
			try
			{
				curr_res = this->matrix[i][j]->add(rhs.matrix[i][j]);
				row.push_back(curr_res);
			}
			catch(const std::exception& e)
			{
				throw Ft_error(std::string(e.what()));
			}
			
		}
		res.add_row(row);
	}
	return res;
}

Matrix Matrix::operator-(const Matrix &rhs)
{
	Matrix	res;
	BaseAssignmentType *curr_res;

	if ((this->num_rows != rhs.num_rows) || (this->num_cols != rhs.num_cols)) 
		throw Ft_error("Cannot perform operation on bad size");
	for (int i = 0; i < this->num_rows; i++)
	{
		std::vector<BaseAssignmentType *> row;
		for (int j = 0; j < this->num_cols; j++)
		{
			try
			{
				curr_res = this->matrix[i][j]->sub(rhs.matrix[i][j]);
				row.push_back(curr_res);
			}
			catch(const std::exception& e)
			{
				throw Ft_error(std::string(e.what()));
			}
			
		}
		res.add_row(row);
	}
	return res;
}

Matrix Matrix::operator*(const Matrix &rhs)
{
	Matrix	res;
	int		total_rows;
	int		total_cols;

	// check if matrix is multipliable
	if (this->get_num_cols() != rhs.get_num_rows()) throw Ft_error("Invalid matrix for mult");

	total_rows = this->get_num_rows();
	total_cols = rhs.get_num_cols();

	for (int curr_row_num = 0; curr_row_num < total_rows; curr_row_num++)
	{
		std::vector<BaseAssignmentType *> row;
		for (int curr_col_num = 0; curr_col_num < total_cols; curr_col_num++)
		{
			row.push_back(this->_get_dot_product(*this, rhs, curr_row_num, curr_col_num));
		}
		res.add_row(row);
	}
	
	return res;
}

Matrix Matrix::operator/(Matrix &rhs)
{
	Matrix *inverse;
	Matrix *res_ptr;


	inverse = this->get_inverse_matrix(rhs);
	res_ptr = dynamic_cast<Matrix *> (this->mult(inverse));
	Matrix res((*res_ptr));
	delete inverse;
	delete res_ptr;
	return res;
}

/**
 * Getter and setter
*/
int	Matrix::get_num_cols() const
{
	return this->num_cols;
}

int Matrix::get_num_rows() const
{
	return this->num_rows;
}

std::vector<std::vector<BaseAssignmentType *>>	Matrix::get_matrix()
{
	return this->matrix;
}

std::vector<std::vector<BaseAssignmentType *>>	&Matrix::get_matrix_ref()
{
	return this->matrix;
}

/**
 * validates and set matrix w/o cloning
*/
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
	this->num_rows = 0;
	this->type = N_MATRIX;
}

Matrix::Matrix(std::vector<std::vector<BaseAssignmentType *>>	matrix)
{
	this->set_matrix(matrix);
	this->type = N_MATRIX;
}

Matrix::Matrix(std::string str)
{
	std::vector<std::vector<BaseAssignmentType*>> res;
	std::vector<std::string> row_strs;
	int	row_idx;
	int	col_idx;
	int is_neg;

	is_neg = 0;
	row_idx = -1;

	if (str[0] == '-') is_neg = 1;
	// trim first and last brackets
	std::string::iterator new_end =  std::remove_if(str.begin(), str.end(), isspace);
	// remove_if changes end() pointer
	str.erase(new_end, str.end());
	str.erase(0, 1 + is_neg);
	str.erase(str.size() - 1);

	// split the string into row strings by ';'
	row_strs = ft_split(str, {";"});

	// loop through rows
	while (std::size_t(++row_idx) < row_strs.size())
	{
		std::vector<std::string> col_strs;
		std::vector<BaseAssignmentType *> row;
		std::string row_str;
		BaseAssignmentType *token;
		
		row_str = row_strs[row_idx];

		// trim first and last brackets
		new_end = std::remove_if(row_str.begin(), row_str.end(), isspace);
		row_str.erase(new_end, row_str.end());
		row_str.erase(0, 1);
		row_str.erase(row_str.size() - 1);

		// generate columns
		col_strs = ft_split(row_str, {","});
		col_idx = -1;
		while (std::size_t(++col_idx) < col_strs.size())
		{
			// generate token
			const int type = derive_token_type(col_strs[col_idx]);

			// for now, only accept rational number and imaginary number
			if (type != N_RATIONAL && type != N_IMAGINARY) throw Ft_error("Matrix only accepts numbers");
			else if (type == N_RATIONAL) token = new RationalNumber(float(atof(col_strs[col_idx].c_str())) * (is_neg? -1 : 1));
			else if (type == N_IMAGINARY)
			{
				ImaginaryNumber *res_im = new ImaginaryNumber();

 				// split the big string into 2 small strngs
        		std::vector<std::string> col_tokens = ft_split(col_strs[col_idx], {"+", "-"});

				// only i
				if (col_tokens.size() == 1 && col_tokens[0] == "i")
				{
					res_im->imaginary_part = RationalNumber(1);
					res_im->real_part = RationalNumber(0);
				}
				// determine which is the imaginary part [0] or [1]
				else if (col_tokens[0].find("i") != std::string::npos)
				{
					res_im->imaginary_part = RationalNumber(atoi(col_tokens[0].c_str()));
					if (col_tokens.size() != 1)
						res_im->real_part = RationalNumber(atoi(col_tokens[1].c_str()));
				}
				else
				{
					res_im->imaginary_part = RationalNumber(atoi(col_tokens[1].c_str()));
					res_im->real_part = RationalNumber(atoi(col_tokens[0].c_str()));
				}

				token = res_im;
			}

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
	// free curr matrix
	for (size_t i = 0; i < this->matrix.size(); i++)
		free_tokens(this->matrix[i]);

	// reallocate new matric
	std::vector<std::vector<BaseAssignmentType *>> clone_mat = this->_clone_matrix(other.matrix);
	this->set_matrix(clone_mat);
	this->num_cols = other.num_cols;
	this->num_rows = other.num_rows;
	this->type = N_MATRIX;
}

Matrix & Matrix::operator=(const Matrix &other)
{
	this->set_matrix(other.matrix);
	this->num_cols = other.num_cols;
	this->num_rows = other.num_rows;
	this->type = N_MATRIX;
	return *this;
}

Matrix::~Matrix()
{
	for (size_t i = 0; i < this->matrix.size(); i++)
		free_tokens(this->matrix[i]);
}