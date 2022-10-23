#include "main.hpp"

/**
 * @brief Evaluates the of number a raised by the power of power
 * 
 * @param a 
 * @param power 
 * @return double 
 */
float ft_pow(float a, int power)
{
	if (power == 0)
		return 1;
	if (power == 1)
		return a;
	if (power < 0)
		return 0;
	return (ft_pow((a * a), power - 1));
}

// ADD TYPE
BaseAssignmentType *clone_token(BaseAssignmentType * token)
{
	const int type = token->getType();
	BaseAssignmentType * res;
	
	if (type == VAR)
	{
		Variable *var = dynamic_cast<Variable *>(token);
		res = new Variable(*var);
		return res;
	}
	else if (type == OPERATOR_DIV || type == OPERATOR_EQ || type == OPERATOR_MAT_MULT || type == OPERATOR_MINUS 
		|| type == OPERATOR_MOD || type == OPERATOR_MULT || type == OPERATOR_PLUS || type == OPERATOR_POW)
	{
		Operator *var = dynamic_cast<Operator *>(token);
		res = new Operator(*var);
		return res;
	}
	else if (type == Q_MARK)
	{
		QMark *var = dynamic_cast<QMark *>(token);
		res = new QMark(*var);
		return res;
	}
	else if (type == L_PARENTHESIS || type == R_PARENTHESIS)
	{
		Parenthesis *var = dynamic_cast<Parenthesis *>(token);
		res = new Parenthesis(*var);
		return res;
	}
	else if (type == N_RATIONAL)
	{
		RationalNumber *var = dynamic_cast<RationalNumber *>(token);
		res = new RationalNumber(*var);
		return res;
	}
	else if (type == N_IMAGINARY)
	{
		ImaginaryNumber *var = dynamic_cast<ImaginaryNumber *>(token);
		res = new ImaginaryNumber(*var);
		return res;
	}
	return nullptr;
}