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
			if ((*res)->getType() == L_PARENTHESIS) ++stack_cnt;
			else if ((*res)->getType() == R_PARENTHESIS) --stack_cnt;
			if (stack_cnt == 0) return res;
			++res;
		}
		else
		{
			if ((*res)->getType() == L_PARENTHESIS) --stack_cnt;
			else if ((*res)->getType() == R_PARENTHESIS) ++stack_cnt;
			if (stack_cnt == 0) return res;
			--res;
		}
	}
	return res;
}

static int count_significant_terms(std::vector<BaseAssignmentType *>::iterator start, std::vector<BaseAssignmentType *>::iterator end)
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

static void	token_pairing(std::vector<BaseAssignmentType *> &tokens, std::vector<BaseAssignmentType *>::iterator start, std::vector<BaseAssignmentType *>::iterator end)
{
	// base case, return if no bracket and sig term < 2
	if (std::find_if(start, end, [](BaseAssignmentType* token){return token->getType() == L_PARENTHESIS || token->getType() == R_PARENTHESIS;}) == end
	&& count_significant_terms(start, end) < 2
	)
	{
		return ;
	}

	// recursive call on every sigterm
	std::vector<BaseAssignmentType *>::iterator curr_start;
	std::vector<BaseAssignmentType *>::iterator curr_end;
	int start_offset;
	int	end_offset;
	int	curr_end_offset;
	int	curr_start_offset;

	curr_start = start;
	curr_end = start;
	start_offset = start - tokens.begin();
	end_offset = tokens.end() - end;
	while (curr_start != end)
	{
		// if curr start is parenthesis, find next pair for curr end
		if ((*curr_start)->getType() == L_PARENTHESIS)
		{
			curr_end = find_parenthesis_pair(curr_start, end);

			// save iterators
			// curr_start_offset = curr_start - tokens.begin();
			curr_end_offset = tokens.end() - curr_end;

			// recursive call and trim parenthesis
			token_pairing(tokens, curr_start + 1, curr_end);

			// restore iterators
			curr_end = tokens.end() - curr_end_offset;
			curr_start = curr_end;
			end = tokens.end() - end_offset;
			start = tokens.begin() + start_offset;
		}
		// go to next sigterm
		++curr_start;

		// skip all operators
		while (curr_start != end && is_operator(*curr_start))
			++curr_start;
	}

	// group terms
	// while sig terms in eq is more than 2
	while (count_significant_terms(start, end) > 2)
	{
		// loop through tokens in eq
		curr_start = start;
		while (curr_start != end)
		{
			// get next sig term
			curr_end = curr_start + 1;

			// if curr token is parenthesis, curr_end will start travelling at end of parenthesis
			if ((*curr_start)->getType() == L_PARENTHESIS) curr_end = find_parenthesis_pair(curr_start, end) + 1;
			while (curr_end != end && is_operator(*curr_end))
				++curr_end;

			// if next sig term is a parenthesis, go to other end
			if (curr_end != end && (*curr_end)->getType() == L_PARENTHESIS)
				curr_end = find_parenthesis_pair(curr_end, end);

			// if curr end did not move or curr end is at end of eq, return
			if (curr_end == curr_start + 1 || curr_end == end)
				break ;

			// save iterator offset
			curr_end_offset = tokens.end() - curr_end;

			// add parenthesis before curr start
			tokens.insert(curr_start, new Parenthesis("("));
			print_parsed_tokens_no_format(tokens);

			// add parenthesis after curr end and  move curr start to curr end
			curr_end = tokens.end() - curr_end_offset;
			curr_start = tokens.insert(curr_end + 1, new Parenthesis(")")) + 1;
			print_parsed_tokens_no_format(tokens);

			// restore start and end iterators
			start = tokens.begin() + start_offset;
			end = tokens.end() - end_offset;
			curr_end = tokens.end() - curr_end_offset;

			// skip all operators on curr_start
			while (curr_start != end && is_operator(*curr_start)) curr_start++;

		}
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

	// pair tokens
	token_pairing(tokens, start_iter, end_iter);
	// print_parsed_tokens_no_format(tokens);
}