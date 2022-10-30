#ifndef __MAIN__H__
#define __MAIN__H__
#include "libraries.hpp"
#include "constants.hpp"
#include "tokens.hpp"
#include "ft_error.hpp"
#include "rational_num_operators.hpp"

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
std::string evalaute(std::vector<BaseAssignmentType *> &tokens, bool is_compute_action, std::map<std::string, BaseAssignmentType *> &variables);
void	token_preprocess(std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
ParseTreeNode *generate_parse_tree(std::vector<BaseAssignmentType *> tokens, bool is_compute_action);
BaseAssignmentType *evaluate_parse_tree(ParseTreeNode **head);

// builtins
void	handle_builtin(std::string line, std::map<std::string, std::string> history, std::map<std::string, BaseAssignmentType *> variables);

// utils
std::string ft_tolower(std::string str);
BaseAssignmentType *clone_token(BaseAssignmentType * token);
bool is_operator(BaseAssignmentType* token);
bool is_eq(BaseAssignmentType* token);
std::vector<BaseAssignmentType *>::iterator determine_start_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
std::vector<BaseAssignmentType *>::iterator determine_end_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
bool is_leaf_node(ParseTreeNode * node);
std::string var_to_str(std::map<std::string, BaseAssignmentType *>::iterator iter);

// logging
void	print_unparsed_tokens(std::vector<TokenBase> tokens);
void	print_parsed_tokens(std::vector<BaseAssignmentType *> tokens);
void	print_parsed_tokens_no_format(std::vector<BaseAssignmentType *> tokens);
void	print_tree(ParseTreeNode *head);
void	ft_perror(Ft_error err);
void	ft_pinfo(std::string msg);

// signals
void sigint_handler(int signal);

// memory
void free_token(BaseAssignmentType * token);
void	free_tokens(std::vector<BaseAssignmentType *> tokens);
void	free_variables(std::map<std::string, BaseAssignmentType *> vars);
void	free_tree(ParseTreeNode * curr);

#endif  //!__MAIN__H__