#include "main.hpp"

static std::vector<BaseAssignmentType *>::iterator	find_parenthesis_pair(std::vector<BaseAssignmentType *>::iterator curr, std::vector<BaseAssignmentType *>::iterator end)
{
	int		stack_cnt;
	bool	l2r_direction;
	std::vector<BaseAssignmentType *>::iterator res;


	stack_cnt = 1;
	l2r_direction = true;
	if ((*curr)->getType() != L_PARENTHESIS && (*curr)->getType() != R_PARENTHESIS)
	{
		ft_pinfo(std::to_string((*curr)->getType()));
		return end;
	}
	if ((*curr)->getType() == R_PARENTHESIS) l2r_direction = false;
	res = l2r_direction ? ++curr : --curr;
	while (stack_cnt != 0)
	{
		if (l2r_direction)
		{
			++res;
			if ((*res)->getType() == L_PARENTHESIS) ++stack_cnt;
			else if ((*res)->getType() == R_PARENTHESIS) --stack_cnt;
		}
		else
		{
			--res;
			if ((*res)->getType() == L_PARENTHESIS) --stack_cnt;
			else if ((*res)->getType() == R_PARENTHESIS) ++stack_cnt;
		}
	}
	return res;
}

static void token_populate(std::vector<BaseAssignmentType *>::iterator start, std::vector<BaseAssignmentType *>::iterator end, std::vector<BaseAssignmentType *> tokens)
{
	std::vector<BaseAssignmentType *>::iterator curr;

	curr = start;
	while (curr != end)
	{
		BaseAssignmentType *curr_token = *curr;

		if (curr_token->getType() == L_PARENTHESIS || curr_token->getType() == R_PARENTHESIS)
		{
			std::vector<BaseAssignmentType *>::iterator test = find_parenthesis_pair(curr, end);
		}
		curr++;
	}
	
}

void	token_preprocess(std::vector<BaseAssignmentType *>::iterator start, std::vector<BaseAssignmentType *>::iterator end, std::vector<BaseAssignmentType *> tokens)
{
	// populate tokens
	token_populate(start, end, tokens);

	// pair tokens
}