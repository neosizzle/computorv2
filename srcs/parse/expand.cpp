// #include "main.hpp"
#include "expand.hpp"
std::string tokens_to_str(std::vector<BaseAssignmentType *>::iterator begin, std::vector<BaseAssignmentType *>::iterator end);

/**
 * @brief Returns true if current token is a variable type token
 * 
 * @param i 
 * @return true 
 * @return false 
 */
static bool is_var (BaseAssignmentType *i) {
  return (i->getType() == VAR);
}

/**
 * @brief Expands the variables in a token list to house actual values
 * 
 * @param tokens 
 * @param variables 
 * @param is_compute_action 
 */
void expand_variables(std::vector<BaseAssignmentType *> &tokens, std::map<std::string, BaseAssignmentType *> variables, bool is_compute_action)
{
	bool		is_func_assign;
	std::string qmark_first_var;
	std::vector<BaseAssignmentType *>::iterator tokens_iter;
	std::vector<BaseAssignmentType *>::iterator tokens_iter_init;

	is_func_assign = false;
	// determine if its a function assignment
	if (tokens.size() > 2 && tokens[0]->getType() == FUNC && tokens[1]->getType() == OPERATOR_EQ)
	{
		is_func_assign = true;
		// ft_pinfo( tokens[0]->toString());
		// harvest
	}

	// if end with qmark, determine first var used
	else if (is_compute_action)
	{
		std::vector<BaseAssignmentType *>::iterator found_iter = std::find_if(tokens.begin(), tokens.end(), is_var);
		if (found_iter != tokens.end())
		{
			Variable *qmark_var = dynamic_cast<Variable *>(*found_iter);
			qmark_first_var = ft_tolower(qmark_var->name);
		}
	}

	// move beginning to eq sign if action is not compute
	tokens_iter_init = tokens.begin();
	if (!is_compute_action)
	{
		while (tokens_iter_init != tokens.end() && (*tokens_iter_init)->getType() != OPERATOR_EQ)
			tokens_iter_init++;
	}
	tokens_iter = tokens_iter_init;
	// loop through all tokens
	for (;tokens_iter != tokens.end();++tokens_iter)
	{
		BaseAssignmentType * curr_token = *tokens_iter;

		// if curr token is a variable type
		if (curr_token->getType() == VAR)
		{
			std::map<std::string, BaseAssignmentType *>::iterator found_var_iter;

			// find the actual token inside the variables
			found_var_iter = variables.find(ft_tolower(curr_token->toString()));

			// if token is found and is NOT compute action and NOT polynimial var, expand
			if ((is_compute_action && ft_tolower(curr_token->toString()) == std::string(1, POLYNOMIAL_VAR))) continue ;
			if (found_var_iter != variables.end()){
				// Clone new token
				BaseAssignmentType *new_token = clone_token(found_var_iter->second);

				// reaplce variable with cloned token
				std::replace (tokens_iter_init, tokens.end(), curr_token , new_token);

				// free old variable token
				free_token(curr_token);
			}
		}

		// if curr token is a function type 
		if (curr_token->getType() == FUNC)
		{
			// record offset

			Function * func_token = dynamic_cast<Function *>(curr_token);
			// search for function token in variables

			// if function cant be found, continue 

			// clone and replace function object

			// if function object is var
			if (func_token->get_object()->getType() == VAR)
			{
				// reaplce token with function tokens
			}
			// function object is not var
			else
			{
				// reaplce token with calculated image
			}
			
			// restore offset
		}

	}
	
	// find any leftover variables and functions
	std::vector<std::string> leftover_vars;
	for (; tokens_iter_init != tokens.end(); ++tokens_iter_init)
	{
		if (is_var(*tokens_iter_init))
			leftover_vars.push_back((*tokens_iter_init)->toString());
	}
	
	// erase dupes
	leftover_vars.erase(std::unique(leftover_vars.begin(), leftover_vars.end()), leftover_vars.end());

	// if its a compute action, only one leftoever varaible is allowed
	if (is_compute_action)
	{
		if (leftover_vars.size() > 1) throw Ft_error(std::string("Token not found (compute): ") + leftover_vars.back());
	}

	// if its a function assignment, all leftoever variables must be he function variable 
	else if (is_func_assign)
	{
		// all leftoever variables must be the function variable 
	}
	else if (leftover_vars.size() > 0)
		throw Ft_error(std::string("Token not found (assign): ") + leftover_vars.back());
}