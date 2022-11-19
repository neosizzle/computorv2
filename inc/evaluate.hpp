#ifndef __EVALUATE__H__
#define __EVALUATE__H__

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "Base.hpp"
#include "tokens.hpp"
#include "ParseTreeNode.hpp"
#include "ft_error.hpp"

// eval
void	token_preprocess(std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
ParseTreeNode *generate_parse_tree(std::vector<BaseAssignmentType *> tokens, bool is_compute_action);
BaseAssignmentType *evaluate_parse_tree(ParseTreeNode **head);
std::string compute_polynomial(std::string arg);

// utils
std::string ft_tolower(std::string str);
BaseAssignmentType *clone_token(BaseAssignmentType * token);
std::string var_to_str(std::map<std::string, BaseAssignmentType *>::iterator iter);
std::vector<BaseAssignmentType *>::iterator determine_start_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
std::vector<BaseAssignmentType *>::iterator determine_end_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
bool is_var(BaseAssignmentType * node);
std::string tokens_to_str(std::vector<BaseAssignmentType *>::iterator begin, std::vector<BaseAssignmentType *>::iterator end);

// memory
void free_token(BaseAssignmentType * token);
void	free_tree(ParseTreeNode * curr);

// log
void ft_pinfo(std::string res);

#endif  //!__EVALUATE__H__