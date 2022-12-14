#include "tokens.hpp"
#include "Base.hpp"
#include "constants.hpp"
#include "ft_error.hpp"
#include "Variable.hpp"
#include "Parenthesis.hpp"
#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "Matrix.hpp"
#include "Operator.hpp"
#include "QMark.hpp"
#include "ParseTreeNode.hpp"
#include "Function.hpp"

/**
 * @brief Free individual token
 * 
 * @param token 
 */
// ADD TYPE
void free_token(BaseAssignmentType * token)
{
	if (token == nullptr) return;
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
	else if (type == N_MATRIX)
	{
		Matrix *var = dynamic_cast<Matrix *>(token);
		delete var;
	}
	else if (type == FUNC)
	{
		Function * var = dynamic_cast<Function *>(token);
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

/**
 * @brief Frees a parse tree
 * 
 * @param curr 
 */
void	free_tree(ParseTreeNode * curr)
{
	// Base case, return if curr node is null
	if (curr == nullptr) return;

	// recurse left child
	free_tree(curr->left);

	// recurse right child
	free_tree(curr->right);

	// free content and free curr node
	if (curr->value != nullptr)
		free_token(curr->value);
	delete curr ;	
}