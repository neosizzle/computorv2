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
	BaseAssignmentType *result_stack;

	// determine function assign
	if (tokens.size() > 1 && tokens[0]->getType() == FUNC && tokens[1]->getType() == OPERATOR_EQ)
	{
		// check if function name is found
		Function *func_token = dynamic_cast<Function *>(clone_token(tokens[0]));
		std::map<std::string, BaseAssignmentType *>::iterator found_var_iter;
		std::map<std::string, BaseAssignmentType *>::iterator inserted_iter;

		// clone tokens
		std::vector<BaseAssignmentType *> tokens_cloned(tokens);
		tokens_cloned.erase(tokens_cloned.begin());
		tokens_cloned.erase(tokens_cloned.begin());

		// add tokens to token
		func_token->set_tokens(tokens_cloned);

		// find the actual token inside variables
		found_var_iter = variables.find(ft_tolower(func_token->get_name()));

		// if token is found
		if (found_var_iter != variables.end())
		{
			// free current pointed token
			free_token((*found_var_iter).second);
			variables.erase(found_var_iter);
		}
		// insert to variables
		inserted_iter = variables.insert({ft_tolower(func_token->get_name()), func_token}).first;
		return var_to_str(inserted_iter);

	}

	// if variable is within tokens, call to process polynomial
	if (std::find_if(determine_start_iter(tokens, is_compute_action), tokens.end(), is_var) != tokens.end())
		return compute_polynomial(tokens_to_str(determine_start_iter(tokens, is_compute_action), determine_end_iter(tokens, is_compute_action)));

	// preprocess tokens (populate and pair tokens)
	token_preprocess(tokens, is_compute_action);

	// generate parse tree
	head = generate_parse_tree(tokens, is_compute_action);

	// evaluate parse tree
	try
	{
		result_stack = evaluate_parse_tree(&head);
		if (result_stack == nullptr)
		{
			free_tree (head);
			return "";
		}
	}
	catch(Ft_error &e)
	{
		free_tree(head);
		throw Ft_error(e);
	}
	result = clone_token(result_stack);
	

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
			// (*found_var_iter).second = result;
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