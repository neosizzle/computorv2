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
void expand_variables(std::vector<BaseAssignmentType *> &tokens, std::map<std::string, BaseAssignmentType *> variables, bool is_compuet_action);

// validation
void	validate_tokens(std::vector<BaseAssignmentType *> tokens, bool is_compute_action);

// evaulation
std::string evalaute(std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
void	token_preprocess(std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
ParseTreeNode *generate_parse_tree(std::vector<BaseAssignmentType *>::iterator start, std::vector<BaseAssignmentType *>::iterator end);

// utils
float ft_pow(float a, int power);
BaseAssignmentType *clone_token(BaseAssignmentType * token);

// logging
void	print_unparsed_tokens(std::vector<TokenBase> tokens);
void	print_parsed_tokens(std::vector<BaseAssignmentType *> tokens);
void	print_parsed_tokens_no_format(std::vector<BaseAssignmentType *> tokens);
void	ft_perror(Ft_error err);
void	ft_pinfo(std::string msg);

// signals
void sigint_handler(int signal);

// memory
void free_token(BaseAssignmentType * token);
void	free_tokens(std::vector<BaseAssignmentType *> tokens);
void	free_variables(std::map<std::string, BaseAssignmentType *> vars);

#endif  //!__MAIN__H__