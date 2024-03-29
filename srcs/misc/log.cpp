#include "constants.hpp"
#include <map>
#include <iostream>
#include "tokens.hpp"
#include "Base.hpp"
#include "ft_error.hpp"
#include "ParseTreeNode.hpp"

const std::map<int, std::string> TYPE_MAP = {
		{L_PARENTHESIS, "L_PARENTHESIS"},
		{R_PARENTHESIS, "R_PARENTHESIS"},
		{OPERATOR_PLUS, "OPERATOR_PLUS"},
		{OPERATOR_MINUS, "OPERATOR_MINUS"},
		{OPERATOR_EQ, "OPERATOR_EQ"},
		{OPERATOR_MULT, "OPERATOR_MULT"},
		{OPERATOR_DIV, "OPERATOR_DIV"},
		{OPERATOR_POW, "OPERATOR_POW"},
		{OPERATOR_MOD, "OPERATOR_MOD"},
		{OPERATOR_MAT_MULT, "OPERATOR_MAT_MULT"},
		{Q_MARK, "Q_MARK"},
		{VAR, "VAR"},
		{FUNC, "FUNC"},
		{N_RATIONAL, "N_RATIONAL"},
		{N_IMAGINARY, "N_IMAGINARY"},
		{N_MATRIX, "N_MATRIX"},
		{MATRIX_BRAC_L, "MATRIX_BRAC_L"},
		{MATRIX_BRAC_R, "MATRIX_BRAC_R"},
		{MATRIX_NL, "MATRIX_NL"},
		{MATRIX_SEP, "MATRIX_SEP"},
	};

/**
 * @brief Prints unparsed tokens
 * 
 * @param tokens 
 */
void print_unparsed_tokens(std::vector<TokenBase> tokens)
{
	for (std::vector<TokenBase>::iterator i = tokens.begin(); i != tokens.end(); i++)
		std::cout << "Token string: " << i->string << " | Token type: " << (TYPE_MAP.find(i->type) == TYPE_MAP.end() ? "unknown" : TYPE_MAP.find(i->type)->second) << "\n";
}

/**
 * @brief Prints parsed tokens
 * 
 * @param tokens 
 */
void print_parsed_tokens(std::vector<BaseAssignmentType *> tokens)
{
	for (std::vector<BaseAssignmentType *>::iterator i = tokens.begin(); i != tokens.end(); i++)
	{
		if ( !*i)
		{
			std::cout << "Token string:  null | Token type: null \n";
			continue ;
		}
		std::cout << "Token string: " << (*i)->toString() << " | Token type: " << (TYPE_MAP.find((*i)->getType()) == TYPE_MAP.end() ? "unknown" : TYPE_MAP.find((*i)->getType())->second) << "\n";
	}
}

/**
 * @brief Prints parsed tokens w/o format
 * 
 * @param tokens 
 */
void print_parsed_tokens_no_format(std::vector<BaseAssignmentType *> tokens)
{
	for (std::vector<BaseAssignmentType *>::iterator i = tokens.begin(); i != tokens.end(); i++)
	{
		if ( !*i)
		{
			std::cout << " null ";
			continue ;
		}
		std::cout << " " << (*i)->toString() << " ";
	}
	std::cout <<"\n";
}

/**
 * @brief Prints error message
 * 
 * @param e 
 */
void	ft_perror(Ft_error e)
{
	std::cout << BOLDRED << "[ft_error] " << RESET << RED << e.getMessage() << RESET << "\n";
}

/**
 * @brief Prints info message
 * 
 * @param msg 
 */
void	ft_pinfo(std::string msg)
{
	std::cout << BOLDWHITE << "[ft_info] " << RESET << WHITE << msg << RESET << "\n";
}

/**
 * @brief Helper function to print out a binary tree
 * 
 * @param curr 
 * @param space 
 */
static void	print_tree_helper(ParseTreeNode *curr, int space)
{
	if (curr == nullptr) return;

	space += 10;

	print_tree_helper(curr->right, space);

	// print
	for (int i = 0; i < space; i++)
		std::cout << " ";
	
	std::cout << curr->toString() << "\n";

	print_tree_helper(curr->left, space);
}

/**
 * @brief Prints out a binary tree horizontally
 * 
 * @param head 
 */
void	print_tree(ParseTreeNode *head)
{
	print_tree_helper(head, -10);
}