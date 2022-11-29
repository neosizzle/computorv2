#include "expand.hpp"

#include "unistd.h"
void	ft_pinfo(std::string msg);

std::string tokens_to_str(std::vector<BaseAssignmentType *>::iterator begin, std::vector<BaseAssignmentType *>::iterator end);
void print_parsed_tokens_no_format(std::vector<BaseAssignmentType *> tokens);

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
	int			tokens_iter_init_offset;
	std::string qmark_first_var;
	std::string	func_assign_var;
	std::vector<BaseAssignmentType *>::iterator iter_to_del_func_assign;
	std::vector<BaseAssignmentType *>::iterator tokens_iter;
	std::vector<BaseAssignmentType *>::iterator tokens_iter_init;

	is_func_assign = false;
	// determine if its a function assignment
	if (tokens.size() > 2 && tokens[0]->getType() == FUNC && tokens[1]->getType() == OPERATOR_EQ)
	{
		std::string func_str;
		std::size_t pos_lb;
    	std::size_t pos_rb;
		
		is_func_assign = true;

		// harvest func variable
		func_str = tokens[0]->toString();
		// find first '('
		// find first ')'
		pos_lb = func_str.find("(");
		pos_rb = func_str.find(")");

		// get the string in between
		func_assign_var = func_str.substr(pos_lb + 1, pos_rb - pos_lb - 1);
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
	tokens_iter_init_offset = tokens_iter_init - tokens.begin();
	// loop through all tokens
	for (;tokens_iter != tokens.end();++tokens_iter)
	{
		BaseAssignmentType * curr_token = *tokens_iter;
		// ft_pinfo(curr_token->toString());
		// print_parsed_tokens_no_format(tokens);
		// sleep(1);
		
		// if curr token is a variable type
		if (curr_token->getType() == VAR)
		{
			std::map<std::string, BaseAssignmentType *>::iterator found_var_iter;

			// find the actual token inside the variables
			found_var_iter = variables.find(ft_tolower(curr_token->toString()));

			// if token is found and is NOT compute action and NOT polynimial var and NOT func, expand
			// if ((is_compute_action && ft_tolower(curr_token->toString()) == std::string(1, POLYNOMIAL_VAR))) continue;
			if (found_var_iter != variables.end()){
				// ignore functions in var list
				if (found_var_iter->second->getType() == FUNC)
					continue;

				// Clone new token
				BaseAssignmentType *new_token = clone_token(found_var_iter->second);

				// reaplce variable with cloned token
				std::replace (tokens_iter_init, tokens.end(), curr_token , new_token);

				// free old variable token
				free_token(curr_token);
			}
		}

		// if curr token is a function type 
		else if (curr_token->getType() == FUNC)
		{
			std::map<std::string, BaseAssignmentType *>::iterator found_var_iter;
			int iter_offset;
			Function * func_token;
			BaseAssignmentType *func_obj;

			// record offset
			iter_offset = tokens_iter - tokens.begin();

			// search for function token in variables
			func_token = dynamic_cast<Function *>(curr_token);
			found_var_iter = variables.find(ft_tolower(func_token->get_name()));

			// if function cant be found throw error
			if (found_var_iter == variables.end()) throw Ft_error(std::string("Function not found (expand): ") + func_token->toString());
			if (found_var_iter->second->getType() != FUNC) throw Ft_error(std::string("Not a function (expand): ") + func_token->toString());

			// clone and replace function object
			func_obj = clone_token(func_token->get_object());
			free_token(tokens[iter_offset]);
			tokens[iter_offset] = found_var_iter->second;
			func_token = dynamic_cast<Function *>(found_var_iter->second); // i need to clone here?
			func_token->set_object(func_obj);
			free_token(func_obj);

			// if function object is var
			if (func_token->get_object()->getType() == VAR)
			{
				std::vector<BaseAssignmentType *> func_tokens;

				// reaplce token with function tokens
				func_tokens = func_token->get_tokens();
				tokens.insert(++tokens_iter, func_tokens.begin(), func_tokens.end());
				tokens.erase(tokens.begin() + iter_offset);
				tokens_iter_init = tokens.begin() + tokens_iter_init_offset;
				tokens_iter = tokens_iter_init; // reset position to initial
			}
			// function object is not var
			else
			{
				BaseAssignmentType * evaluated_image;

				// reaplce token with calculated image
				evaluated_image = func_token->evaluate_image();
				iter_to_del_func_assign = tokens.insert(tokens_iter, evaluated_image);
				tokens.erase(++iter_to_del_func_assign);
				tokens_iter = tokens.begin() + iter_offset;
				tokens_iter_init = tokens.begin() + tokens_iter_init_offset;	
			}
		}

	}
	
	// find any leftover variables and functions
	std::vector<std::string> leftover_vars;
	tokens_iter_init = tokens.begin() + tokens_iter_init_offset;
	for (; tokens_iter_init != tokens.end(); ++tokens_iter_init)
	{
		if (is_var(*tokens_iter_init))
			leftover_vars.push_back((*tokens_iter_init)->toString());
		if ((*tokens_iter_init)->getType() == FUNC)
			leftover_vars.push_back(dynamic_cast<Function *>(*tokens_iter_init)->get_name());
	}
	
	// erase dupes
	leftover_vars.erase(std::unique(leftover_vars.begin(), leftover_vars.end()), leftover_vars.end());



	// if its a function assignment, all leftoever variables must be he function variable 
	if (is_func_assign)
	{
		// all leftoever variables must be the function variable 
		for (size_t i = 0; i < leftover_vars.size(); ++i)
			if (leftover_vars[i] != func_assign_var) throw Ft_error(std::string("Token not found (compute): ") + leftover_vars[i]);

	}
	// if its a compute action, only one leftoever varaible is allowed
	else if (is_compute_action)
	{
		if (leftover_vars.size() > 1 ) throw Ft_error(std::string("Token not found (compute): ") + leftover_vars.back());
	}
	else if (leftover_vars.size() > 0)
		throw Ft_error(std::string("Token not found (assign): ") + leftover_vars.back());
}