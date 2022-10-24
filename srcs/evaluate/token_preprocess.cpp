#include "main.hpp"

/**
 * @brief Determine start iter for assignment or compute equations 
 * 
 * @param tokens 
 * @param is_compute_action 
 * @return std::vector<BaseAssignmentType *>::iterator 
 */
static std::vector<BaseAssignmentType *>::iterator determine_start_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action)
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
static std::vector<BaseAssignmentType *>::iterator determine_end_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action)
{
	std::vector<BaseAssignmentType *>::iterator res = tokens.end();

	if (!is_compute_action) return res;
	else
	{
		res -= 2;
		if (res != tokens.begin() && (*res)->getType() == OPERATOR_EQ) --res;
		return res;
	}
}

/**
 * @brief Looks for other parenthesis pair
 * 
 * @param curr 
 * @param end 
 * @return std::vector<BaseAssignmentType *>::iterator 
 */
static std::vector<BaseAssignmentType *>::iterator	find_parenthesis_pair(std::vector<BaseAssignmentType *>::iterator curr, std::vector<BaseAssignmentType *>::iterator end)
{
	int		stack_cnt;
	bool	l2r_direction;
	std::vector<BaseAssignmentType *>::iterator res;


	stack_cnt = 1;
	l2r_direction = true;
	if ((*curr)->getType() != L_PARENTHESIS && (*curr)->getType() != R_PARENTHESIS)
		return end;
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

static int count_sigificant_terms(std::vector<BaseAssignmentType *>::iterator start, std::vector<BaseAssignmentType *>::iterator end)
{
	int	terms;
	std::vector<BaseAssignmentType *>::iterator curr_iter;
	BaseAssignmentType * curr_token;

	terms = 0;
	curr_iter = start;
	while (curr_iter != end)
	{
		curr_token = *curr_iter;

		++terms;
		
		// curr term is backet
		if (curr_token->getType() == L_PARENTHESIS)
			curr_iter = find_parenthesis_pair(curr_iter, end);
		
		// move iter till operator
		while (curr_iter != end && !is_operator(curr_token))
			curr_token = *(curr_iter++);
		
	}
	
	return terms;
}

/**
 * @brief Populate parenthesis around BODMAS operators 
 * 
 * 1. loop through all tokens
 * 	- if curr token is bodmas token
 * 	- find prev token. If its parenthesis, go to other end.
 *  - add parenthesis before prev token
 * 	- find next token. If its parenthesis, go to other end.
 * 	- add parenthesis after next token
 * 
 * 
 * @param start 
 * @param end 
 * @param tokens 
 */
static void token_populate(std::vector<BaseAssignmentType *>::iterator &start, std::vector<BaseAssignmentType *>::iterator &end, std::vector<BaseAssignmentType *> &tokens)
{
	std::vector<BaseAssignmentType *>::iterator curr;
	std::vector<BaseAssignmentType *>::iterator prev_token;
	std::vector<BaseAssignmentType *>::iterator next_token;
	std::vector<BaseAssignmentType *>::iterator iter_to_add;
	int		curr_offset;
	int		end_offset;
	int		start_offset;

	end_offset = end - tokens.begin();
	start_offset = start - tokens.begin();

	// Order loop
	curr = start;
	while (curr != end)
	{
		BaseAssignmentType *curr_token = *curr;

		if (curr_token->getType() == OPERATOR_POW)
		{
			curr_offset = curr - tokens.begin();

			prev_token = curr - 1;
			if ((*prev_token)->getType() == L_PARENTHESIS || (*prev_token)->getType() == R_PARENTHESIS )
				iter_to_add = find_parenthesis_pair(prev_token, end);
			else iter_to_add = prev_token;
			tokens.insert(iter_to_add, new Parenthesis((*prev_token)->getType() == L_PARENTHESIS ? ")" : "("));

			// restore curr
			curr = tokens.begin() + ++curr_offset;

			// restore end
			end = tokens.begin() + ++end_offset;

			// next token
			next_token = curr + 1;
			if ((*next_token)->getType() == L_PARENTHESIS || (*next_token)->getType() == R_PARENTHESIS )
				iter_to_add = find_parenthesis_pair(next_token, end) + 1;
			else iter_to_add = next_token + 1;
			tokens.insert(iter_to_add, new Parenthesis((*next_token)->getType() == R_PARENTHESIS ? "(" : ")"));

			// restore curr
			curr = tokens.begin() + curr_offset + 1;

			// restore end
			end = tokens.begin() + end_offset + 1;
		}
		curr++;
	}

	// restore start
	start = tokens.begin() + start_offset;
	
	// DM loop
	curr = start;
	while (curr != end)
	{
		BaseAssignmentType *curr_token = *curr;

		if (curr_token->getType() == OPERATOR_MULT || curr_token->getType() == OPERATOR_DIV || curr_token->getType() == OPERATOR_POW)
		{
			curr_offset = curr - tokens.begin();

			prev_token = curr - 1;
			if ((*prev_token)->getType() == L_PARENTHESIS || (*prev_token)->getType() == R_PARENTHESIS )
				iter_to_add = find_parenthesis_pair(prev_token, end);
			else iter_to_add = prev_token;
			tokens.insert(iter_to_add, new Parenthesis((*prev_token)->getType() == L_PARENTHESIS ? ")" : "("));

			// restore curr
			curr = tokens.begin() + ++curr_offset;

			// restore end
			end = tokens.begin() + ++end_offset;

			// next token
			next_token = curr + 1;
			if ((*next_token)->getType() == L_PARENTHESIS || (*next_token)->getType() == R_PARENTHESIS )
				iter_to_add = find_parenthesis_pair(next_token, end) + 1;
			else iter_to_add = next_token + 1;
			tokens.insert(iter_to_add, new Parenthesis((*next_token)->getType() == R_PARENTHESIS ? "(" : ")"));

			// restore curr
			curr = tokens.begin() + curr_offset + 1;

			// restore end
			end = tokens.begin() + end_offset + 1;
		}
		curr++;
	}
	
}

/**
 * @brief Processes tokens for parse tree generation
 * 
 * @param tokens 
 * @param is_compute_action 
 */
void	token_preprocess(std::vector<BaseAssignmentType *> &tokens, bool is_compute_action)
{
	std::vector<BaseAssignmentType *>::iterator start_iter;
	std::vector<BaseAssignmentType *>::iterator end_iter;

	// determine start and end iter
	start_iter = determine_start_iter(tokens, is_compute_action);
	end_iter = determine_end_iter(tokens, is_compute_action);

	// populate tokens
	token_populate(start_iter, end_iter, tokens);

	// redetermine start and end iter since token changed
	start_iter = determine_start_iter(tokens, is_compute_action);
	end_iter = determine_end_iter(tokens, is_compute_action);

	// ft_pinfo("calling cntsigterm");
	ft_pinfo("Sig terms : " + std::to_string(count_sigificant_terms(start_iter, end_iter)));

	// pair tokens
}