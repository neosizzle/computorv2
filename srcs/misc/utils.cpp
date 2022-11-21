#include "Variable.hpp"
#include "Operator.hpp"
#include "QMark.hpp"
#include "Parenthesis.hpp"
#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "ParseTreeNode.hpp"
#include "constants.hpp"
#include "Function.hpp"

/**
 * @brief Given a string and a list of strings to search for, find the
 * long string for each strings provided
 * 
 * @param string 
 * @param delims 
 * @return std::size_t position of found string if any
 */
std::size_t find_delims_in_str(std::string string, std::vector<std::string> delims, int &found_delim_pos)
{
	int	i;
	std::size_t res;

	i = -1;
	res = std::string::npos;
	while (++i < delims.size())
	{
		res = string.find(delims[i]);
		if (res != std::string::npos)
		{
			found_delim_pos = i;
			return res;
		}
	}
	return res;
}

/**
 * @brief splits a long str into an array of smaller strings with deli mas the 
 * deliminitor
 * 
 * @param str 
 * @param delim 
 * @return std::vector<std::string> 
 */
std::vector<std::string> ft_split(std::string str, std::vector<std::string> delims)
{
	std::size_t currpos;
	std::string token;
	std::vector<std::string> res;
	int	found_delim_pos;

	currpos = 0;
	found_delim_pos = -1;
	// run as long as we have delims in our string
	while ((currpos = find_delims_in_str(str, delims, found_delim_pos)) != std::string::npos)
	{
		// extract token
		token = str.substr(0, currpos);	

		// add to arr
		res.push_back(token);

		// trim out the added token along with its delim
		str.erase(0, currpos + delims[found_delim_pos].length());
	}
	return res;
}

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
 * @brief calls tostring on all tokens and returns result
 * 
 */
std::string tokens_to_str(std::vector<BaseAssignmentType *>::iterator begin, std::vector<BaseAssignmentType *>::iterator end)
{
	std::string res;
	
	while (begin != end)
	{
		// std::cout << (*begin)->toString();
		res.append((*begin)->toString());
		++begin;
	}
	
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
	else if (type == FUNC)
	{
		Function *var = dynamic_cast<Function *>(token);
		res = new Function(*var);
		return res;
	}
	return nullptr;
}

std::vector<BaseAssignmentType *> clone_tokens(std::vector<BaseAssignmentType *> tokens)
{
	std::vector<BaseAssignmentType *> res;
	BaseAssignmentType *temp;
	int	i;

	i = -1;
	while(++i < tokens.size()){
		temp = clone_token(tokens[i]);
		res.push_back(temp);
	}
	return res;
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

/**
 * @brief Determines if current token is type var
 * 
 * @param node 
 * @return true 
 * @return false 
 */
bool is_var(BaseAssignmentType * node)
{
	return node != nullptr && node->getType() == VAR;
}

/**
 * @brief Derive token type from string
 * 
 * @param str 
 * @return int 
 */
int derive_token_type(std::string str)
{
	// check imaginary numbers
	if (str.find('i') != std::string::npos)
		return N_IMAGINARY;

	// check matrix
	if (str.find('[') != std::string::npos)
		return N_MATRIX;
	
	// check qmark
	if (str == "?")
		return Q_MARK;

	// check if string has num only
	int num_only = 1;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] > '9' || str[i] < '0')
		{
			--num_only;
			break;
		}
	}
	if (num_only) return N_RATIONAL;

	
	// check operators TODO

	// return var
	return VAR;
}