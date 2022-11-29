#include "Matrix.hpp"

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


