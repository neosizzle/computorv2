#include "main.hpp"

/**
 * @brief Evaluates current token list and returns result to be printed
 * 
 * @param tokens 
 * @param is_compute_action 
 * @return std::string 
 */
std::string evalaute(std::vector<BaseAssignmentType *> &tokens, bool is_compute_action)
{
	ParseTreeNode *head;

	// preprocess tokens (populate and pair tokens)
	token_preprocess(tokens, is_compute_action);

	// generate parse tree

	// evaluate parse tree

	// result to store or to string return
}