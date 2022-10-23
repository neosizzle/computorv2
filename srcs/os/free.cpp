#include "main.hpp"

/**
 * @brief Free individual token
 * 
 * @param token 
 */
// ADD TYPE
void free_token(BaseAssignmentType * token)
{
	const int type = token->getType();

	if (type == VAR)
	{
		Variable *var = dynamic_cast<Variable *>(token);
		delete var;
	}
	else if (type == OPERATOR_DIV || type == OPERATOR_EQ || type == OPERATOR_MAT_MULT || type == OPERATOR_MINUS 
		|| type == OPERATOR_MOD || type == OPERATOR_MULT || type == OPERATOR_PLUS || type == OPERATOR_POW)
	{
		Operator *var = dynamic_cast<Operator *>(token);
		delete var;
	}
	else if (type == Q_MARK)
	{
		QMark *var = dynamic_cast<QMark *>(token);
		delete var;
	}
	else if (type == L_PARENTHESIS || type == R_PARENTHESIS)
	{
		Parenthesis *var = dynamic_cast<Parenthesis *>(token);
		delete var;
	}
	else if (type == N_RATIONAL)
	{
		RationalNumber *var = dynamic_cast<RationalNumber *>(token);
		delete var;
	}
	else if (type == N_IMAGINARY)
	{
		ImaginaryNumber *var = dynamic_cast<ImaginaryNumber *>(token);
		delete var;
	}
}

/**
 * @brief Frees a token list
 * 
 * @param tokens 
 */
void	free_tokens(std::vector<BaseAssignmentType *> tokens)
{
	for (std::vector<BaseAssignmentType *>::iterator i = tokens.begin(); i != tokens.end(); i++)
	{
		BaseAssignmentType *curr = *i;
		free_token(curr);
	}
}

/**
 * @brief Frees a variable list
 * 
 * @param tokens 
 */
void	free_variables(std::map<std::string, BaseAssignmentType *> vars)
{
	for (std::map<std::string, BaseAssignmentType *>::iterator i = vars.begin(); i != vars.end(); i++)
	{
		BaseAssignmentType * curr = i->second;
		free_token(curr);
	}
	
}
