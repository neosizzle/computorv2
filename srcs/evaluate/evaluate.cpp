#include "main.hpp"

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
 * @brief Evaluates current token list and returns result to be printed
 * 
 * @param tokens 
 * @param is_compute_action 
 * @return std::string 
 */
std::string evalaute(std::vector<BaseAssignmentType *> tokens, bool is_compute_action)
{
	std::vector<BaseAssignmentType *>::iterator start_iter;
	std::vector<BaseAssignmentType *>::iterator end_iter;
	ParseTreeNode *head;

	// determine start and end token
	start_iter = determine_start_iter(tokens, is_compute_action);
	end_iter = determine_end_iter(tokens, is_compute_action);

	// preprocess tokens (populate and pair tokens)
	token_preprocess(start_iter, end_iter, tokens);
	print_parsed_tokens(tokens);

	// generate parse tree

	// evaluate parse tree

	// result to store or to string return
}