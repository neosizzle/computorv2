#include "main.hpp"

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

void print_unparsed_tokens(std::vector<TokenBase> tokens)
{
	for (std::vector<TokenBase>::iterator i = tokens.begin(); i != tokens.end(); i++)
		std::cout << "Token string: " << i->string << " | Token type: " << (TYPE_MAP.find(i->type) == TYPE_MAP.end() ? "unknown" : TYPE_MAP.find(i->type)->second) << "\n";
}

void print_parsed_tokens(std::vector<BaseAssignmentType *> tokens)
{
	for (std::vector<BaseAssignmentType *>::iterator i = tokens.begin(); i != tokens.end(); i++)
	{
		if ( !*i)
		{
			std::cout << "Token string:  null | Token type: null \n";
			continue ;
		}

		// if ((*i)->getType() == VAR)
		// {
		// 	Variable *test = dynamic_cast<Variable *>(*i); // dynamic cast needed
		// 	std::cout << "oo im a var my value is " << test->name << "\n";
		// }
		std::cout << "Token string: " << (*i)->toString() << " | Token type: " << (TYPE_MAP.find((*i)->getType()) == TYPE_MAP.end() ? "unknown" : TYPE_MAP.find((*i)->getType())->second) << "\n";
	}
}


void	ft_perror(Ft_error e)
{
	std::cout << BOLDRED << "[ft_error] " << RESET << RED << e.getMessage() << RESET << "\n";
}