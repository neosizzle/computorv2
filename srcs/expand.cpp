#include "main.hpp"

static bool is_var (BaseAssignmentType *i) {
  return (i->getType() == VAR);
}


void expand_variables(std::vector<BaseAssignmentType *> &tokens, std::map<std::string, BaseAssignmentType *> variables)
{
	bool		is_func_assign;
	bool		is_qmark;
	std::string qmark_first_var;

	is_func_assign = false;
	is_qmark = false;
	// determine if its a function assignment
	if (tokens.size() > 2 && tokens[0]->getType() == FUNC && tokens[1]->getType() == OPERATOR_EQ)
	{
		is_func_assign = true;
		// get function var
	}

	// if end with qmark, determine first var used
	else if (tokens.size() > 2 && tokens[tokens.size() - 1]->getType() == Q_MARK)
	{
		is_qmark = true;
		std::vector<BaseAssignmentType *>::iterator found_iter = std::find_if(tokens.begin(), tokens.end(), is_var);
		if (found_iter != tokens.end())
		{
			Variable *qmark_var = dynamic_cast<Variable *>(*found_iter);
			qmark_first_var = qmark_var->name;
		}
	}

	// loop through all tokens
	for (std::vector<BaseAssignmentType *>::iterator iter = tokens.begin(); iter != tokens.end(); ++iter)
	{
		BaseAssignmentType * curr_token = *iter;

		// if curr token is a variable type
		if (curr_token->getType() == VAR)
		{
			std::map<std::string, BaseAssignmentType *>::iterator found_var_iter;

			// if token is first var of qmark, continue
			if (is_qmark && curr_token->toString() == qmark_first_var) continue;

			// find the actual token inside the variables
			found_var_iter = variables.find(curr_token->toString());

			// if token is not function variable, throw err


			// if token not found, throw err
			if (found_var_iter == variables.end())  throw Ft_error(std::string("Token not found, ") + curr_token->toString());

			// expand said token
		}
	}
	
}