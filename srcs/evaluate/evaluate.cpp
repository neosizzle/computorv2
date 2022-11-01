#include "evaluate.hpp"

/**
 * @brief Evaluates current token list and returns result to be printed
 * 
 * @param tokens 
 * @param is_compute_action 
 * @return std::string 
 */
std::string evalaute(std::vector<BaseAssignmentType *> &tokens, bool is_compute_action, std::map<std::string, BaseAssignmentType *> &variables)
{
	ParseTreeNode *head;
	BaseAssignmentType *result;

	// preprocess tokens (populate and pair tokens)
	token_preprocess(tokens, is_compute_action);

	// generate parse tree
	head = generate_parse_tree(tokens, is_compute_action);

	// evaluate parse tree
	result = clone_token(evaluate_parse_tree(&head));

	// result to store or to string return
	if (!is_compute_action)
	{
		BaseAssignmentType *var_token;

		var_token = tokens[0];

		// check if var string is found 
		std::map<std::string, BaseAssignmentType *>::iterator found_var_iter;
		std::map<std::string, BaseAssignmentType *>::iterator inserted_iter;

		// find the actual token inside the variables
		found_var_iter = variables.find(ft_tolower(var_token->toString()));
		
		// if token is found
		if (found_var_iter != variables.end())
		{
			// free current pointed token
			free_token((*found_var_iter).second);
			(*found_var_iter).second = result;
			variables.erase(found_var_iter);
		}
		free_tree (head);
		inserted_iter = variables.insert({ft_tolower(var_token->toString()), result}).first;
		return var_to_str(inserted_iter);
	}

	free_tree(head);

	// return generated string
	std::string res_str = result->toString();
	free_token(result);
	return res_str;
}