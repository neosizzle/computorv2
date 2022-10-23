#include "main.hpp"

static bool is_operator(BaseAssignmentType* token)
{
	if (token->getType() == OPERATOR_DIV || token->getType() == OPERATOR_EQ
	|| token->getType() == OPERATOR_MAT_MULT || token->getType() == OPERATOR_MINUS || token->getType() == OPERATOR_MOD
	|| token->getType() == OPERATOR_MULT || token->getType() == OPERATOR_PLUS || token->getType() == OPERATOR_POW)
		return true;

	return false;
}

static bool is_eq(BaseAssignmentType* token)
{
	return token->getType() == OPERATOR_EQ;
}

void	validate_tokens(std::vector<BaseAssignmentType *> tokens, bool is_compute_action)
{
	int	parenthesis_stk_cnt;

	parenthesis_stk_cnt = 0;

	// if its a assign task, can only have 1 term before =
	if (!is_compute_action)
	{
		if (tokens.size() > 2 && tokens[1]->getType() != OPERATOR_EQ) throw Ft_error("Can only have 1 term before '='");
	}

	// must not have more than 1 '='
	if (std::count_if(tokens.begin(), tokens.end(), is_eq) > 1) throw Ft_error("Can only have 1 '='");

	// loop through tokens
	for (std::vector<BaseAssignmentType *>::iterator i = tokens.begin(); i != tokens.end(); i++)
	{
		BaseAssignmentType *curr_token = *i;

		// operators can not be next to each other
		if ((i != tokens.begin()) && i != tokens.end() - 1 && is_operator(curr_token) && (is_operator(*(i-1)) || is_operator(*(i+1))))
			throw Ft_error("Operators cant be next to each other");

		// operators cant be at the end 
		if (is_operator(curr_token) && i == tokens.end() - 1) throw Ft_error("Term expected after operator");

		// no variables should have name i
		if (curr_token->getType() == VAR && curr_token->toString() == "i") throw Ft_error("Variable name 'i' is forbidden");

		// if curr token is a left parenthesis, increm stack cnt and vice versa
		if (curr_token->getType() == L_PARENTHESIS) ++parenthesis_stk_cnt;

		if (curr_token->getType() == R_PARENTHESIS) --parenthesis_stk_cnt;
	}

	// if parenthesis does not match, throw err
	if (parenthesis_stk_cnt != 0) throw Ft_error("Parenthesis does not match");
}