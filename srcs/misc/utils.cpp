#include "Variable.hpp"
#include "Operator.hpp"
#include "QMark.hpp"
#include "Parenthesis.hpp"
#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "ParseTreeNode.hpp"

/**
 * @brief Convertes string to lwoercase 
 * 
 * @param str 
 * @return std::string 
 */
std::string ft_tolower(std::string str)
{
	std::string res(str);

	for (size_t i = 0; i < res.size(); i++)
		res[i] = std::tolower(str[i]);
	
	return res;
}

/**
 * @brief Converts var pair to string
 * 
 * @param iter 
 * @return std::string 
 */
std::string var_to_str(std::map<std::string, BaseAssignmentType *>::iterator iter)
{
	std::string var_name;
	BaseAssignmentType *var_val;
	std::string			res;

	var_name = (*iter).first;
	var_val = (*iter).second;
	res = std::string("");

	res.append(var_name + "=" + var_val->toString());
	return res;
}

/**
 * @brief Allocates memory and clones token
 * 
 * @param token 
 * @return BaseAssignmentType* 
 */
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

/**
 * @brief Returns true if token is an operator
 * 
 * @param token 
 * @return true 
 * @return false 
 */
bool is_operator(BaseAssignmentType* token)
{
	if (token->getType() == OPERATOR_DIV || token->getType() == OPERATOR_EQ
	|| token->getType() == OPERATOR_MAT_MULT || token->getType() == OPERATOR_MINUS || token->getType() == OPERATOR_MOD
	|| token->getType() == OPERATOR_MULT || token->getType() == OPERATOR_PLUS || token->getType() == OPERATOR_POW)
		return true;

	return false;
}

/**
 * @brief Returns true if token is '='
 * 
 * @param token 
 * @return true 
 * @return false 
 */
bool is_eq(BaseAssignmentType* token)
{
	return token->getType() == OPERATOR_EQ;
}


/**
 * @brief Determine start iter for assignment or compute equations 
 * 
 * @param tokens 
 * @param is_compute_action 
 * @return std::vector<BaseAssignmentType *>::iterator 
 */
std::vector<BaseAssignmentType *>::iterator determine_start_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action)
{
	std::vector<BaseAssignmentType *>::iterator res = tokens.begin();

	if (is_compute_action) return res;
	else
	{
		while (res != tokens.end() && (*(res++))->getType() != OPERATOR_EQ){}
		return res;
	}
}

/**
 * @brief Determine end iter for assignment or compute equations 
 * 
 * @param tokens 
 * @param is_compute_action 
 * @return std::vector<BaseAssignmentType *>::iterator 
 */
std::vector<BaseAssignmentType *>::iterator determine_end_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action)
{
	std::vector<BaseAssignmentType *>::iterator res = tokens.end();

	if (!is_compute_action) return res;
	else
	{
		--res;
		if (res != tokens.begin() && (*(res-1))->getType() == OPERATOR_EQ) --res;
		return res;
	}
}

/**
 * @brief Determines if current node is a leaf node
 * 
 * @param node 
 * @return true 
 * @return false 
 */
bool is_leaf_node(ParseTreeNode * node)
{

	return node == nullptr || (node->left == nullptr && node->right == nullptr);
}