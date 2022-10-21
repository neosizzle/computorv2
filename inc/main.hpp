#ifndef __MAIN__H__
#define __MAIN__H__
#include "libraries.hpp"
#include "constants.hpp"
#include "tokens.hpp"
#include "ft_error.hpp"

// Computor
void	computor();

// tokens
std::vector<TokenBase>	tokenize(std::string line);
std::vector<BaseAssignmentType *>	parse_tokens(std::vector<TokenBase> tokens);

// expand
void expand_variables(std::vector<BaseAssignmentType *> &tokens, std::map<std::string, BaseAssignmentType *> variables);

// utils
float ft_pow(float a, int power);

// logging
void	print_unparsed_tokens(std::vector<TokenBase> tokens);
void	print_parsed_tokens(std::vector<BaseAssignmentType *> tokens);
void	ft_perror(Ft_error err);

// signals
void sigint_handler(int signal);

#endif  //!__MAIN__H__