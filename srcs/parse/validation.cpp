#include "validation.hpp"

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

		if (is_operator(curr_token))
		{
			if (i != tokens.end() - 1)
			{
				// operator cant be nxt to qmark 
				if ((*(i + 1))->getType() == Q_MARK) throw Ft_error("Operators cant be next to QMARK");
				// right of operator cant be right parenthesis 
				if ((*(i + 1))->getType() == R_PARENTHESIS) throw Ft_error("Right of operator cant be R_PARENTHESES");
			}
			if (i != tokens.begin())
			{
				// operator cant be nxt to qmark 
				if ((*(i - 1))->getType() == Q_MARK) throw Ft_error("Operators cant be next to QMARK");
				// left of operator cant be left parenthesis 
				if ((*(i - 1))->getType() == L_PARENTHESIS) throw Ft_error("Left of operator cant be L_PARENTHESES");
			}

		}

		// operators cant be at the end 
		if (is_operator(curr_token) && i == tokens.end() - 1) throw Ft_error("Term expected after operator");

		// no variables should have name i
		if (curr_token->getType() == VAR && curr_token->toString() == "i") throw Ft_error("Variable name 'i' is forbidden");

		// if curr token is a left parenthesis, increm stack cnt and vice versa
		if (curr_token->getType() == L_PARENTHESIS)
		{
			++parenthesis_stk_cnt;

			// check for empty parenthesis
			if ((i + 1) != tokens.end() && (*(i + 1))->getType() == R_PARENTHESIS) throw Ft_error("Empty parenthesis not allowed");
		}

		// if token ls R Parenthese and there no L parenthesis, throw err
		if (curr_token->getType() == R_PARENTHESIS)
		{
			if (parenthesis_stk_cnt == 0) throw Ft_error("Bad parenthesis");
			--parenthesis_stk_cnt;
		}
	}

	// if parenthesis does not match, throw err
	if (parenthesis_stk_cnt != 0) throw Ft_error("Parenthesis does not match");
}