#ifndef __COMPUTOR__H__
#define __COMPUTOR__H__

#include <map>
#include <iostream>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>
#include <algorithm>

#include "tokens.hpp"
#include "Base.hpp"
#include "constants.hpp"
#include "ft_error.hpp"

// builtins
void	handle_builtin(std::string line, std::map<std::string, std::string> history, std::map<std::string, BaseAssignmentType *> variables);

// tokens
std::vector<TokenBase>	tokenize(std::string line);
std::vector<BaseAssignmentType *>	parse_tokens(std::vector<TokenBase> tokens);

// expand
void expand_variables(std::vector<BaseAssignmentType *> &tokens, std::map<std::string, BaseAssignmentType *> variables, bool is_compuet_action);

// validation
void	validate_tokens(std::vector<BaseAssignmentType *> tokens, bool is_compute_action);

// evaulation
std::string evalaute(std::vector<BaseAssignmentType *> &tokens, bool is_compute_action, std::map<std::string, BaseAssignmentType *> &variables);

// logging
void	ft_perror(Ft_error err);

// memory
void	free_tokens(std::vector<BaseAssignmentType *> tokens);
void	free_variables(std::map<std::string, BaseAssignmentType *> vars);


#endif  //!__COMPUTOR__H__