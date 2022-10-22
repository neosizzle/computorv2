#include "main.hpp"

static bool is_operator(BaseAssignmentType* token)
{
	if (token->getType() == OPERATOR_DIV || token->getType() == OPERATOR_EQ
	|| token->getType() == OPERATOR_MAT_MULT || token->getType() == OPERATOR_MINUS || token->getType() == OPERATOR_MOD
	|| token->getType() == OPERATOR_MULT || token->getType() == OPERATOR_PLUS || token->getType() == OPERATOR_POW)
		return true;

	return false;
}

void	validate_tokens(std::vector<BaseAssignmentType *> tokens, bool is_compute_action)
{
	// if its a assign task, can only have 1 term before =
	if (!is_compute_action)
	{
		if (tokens.size() > 2 && tokens[1]->getType() != OPERATOR_EQ) throw Ft_error("Can only have 1 term before '='");
	}

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
	}
}