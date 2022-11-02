#ifndef __PARSETREE__H__
#define __PARSETREE__H__

#include <vector>
#include <map>

#include "Base.hpp"
#include "ParseTreeNode.hpp"
#include "constants.hpp"
#include "ft_error.hpp"

// utils
std::vector<BaseAssignmentType *>::iterator determine_start_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
std::vector<BaseAssignmentType *>::iterator determine_end_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
std::string ft_tolower(std::string str);
BaseAssignmentType *clone_token(BaseAssignmentType * token);
bool is_operator(BaseAssignmentType* token);
bool is_leaf_node(ParseTreeNode * node);

// logging
void	print_parsed_tokens_no_format(std::vector<BaseAssignmentType *> tokens);
void	print_parsed_tokens(std::vector<BaseAssignmentType *> tokens);

// free
void	free_tree(ParseTreeNode * curr);

#endif  //!__PARSETREE__H__