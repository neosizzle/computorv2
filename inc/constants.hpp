#ifndef __CONSTANTS__H__
#define __CONSTANTS__H__
#include <iostream>
#include <vector>
#include <map>
// colors
#define RESET "\033[0m"
#define BLACK "\033[30m"			  /* Black */
#define RED "\033[31m"				  /* Red */
#define GREEN "\033[32m"			  /* Green */
#define YELLOW "\033[33m"			  /* Yellow */
#define BLUE "\033[34m"				  /* Blue */
#define MAGENTA "\033[35m"			  /* Magenta */
#define CYAN "\033[36m"				  /* Cyan */
#define WHITE "\033[37m"			  /* White */
#define BOLDBLACK "\033[1m\033[30m"	  /* Bold Black */
#define BOLDRED "\033[1m\033[31m"	  /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"	  /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"	  /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"	  /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"	  /* Bold White */

// prompt
const std::string PROMPT = std::string(BOLDWHITE) + "computor> " + std::string(RESET);

// builtin commands list
const std::vector<std::string> COMMANDS = {"list", "history"};

// token types
#define L_PARENTHESIS 0
#define R_PARENTHESIS 1
#define OPERATOR_PLUS 2
#define OPERATOR_MINUS 3
#define OPERATOR_EQ 4
#define OPERATOR_MULT 5
#define OPERATOR_DIV 6
#define OPERATOR_POW 7
#define OPERATOR_MOD 8
#define OPERATOR_MAT_MULT 9
#define Q_MARK 10
#define VAR 11
#define FUNC 12
#define N_RATIONAL 13
#define N_IMAGINARY 14
#define N_MATRIX 15
#define MATRIX_BRAC_L 16
#define MATRIX_BRAC_R 17
#define MATRIX_NL 18
#define MATRIX_SEP 19

// error types
#define FT_ERR_OK 0
#define FT_ERR_NOT_FOUND 1
#define FT_ERR_MISC 69

// polynimial var
#define POLYNOMIAL_VAR 'x'

// lexicographical tokens
const std::map<std::string, int> LEX_TOKENS_MAP = {
	{"(", L_PARENTHESIS},
	{")", R_PARENTHESIS},
	{"+", OPERATOR_PLUS},
	{"-", OPERATOR_MINUS},
	{"*", OPERATOR_MULT},
	{"/", OPERATOR_DIV},
	{"=", OPERATOR_EQ},
	{"%", OPERATOR_MOD},
	{"^", OPERATOR_POW},
	{"**", OPERATOR_MAT_MULT},
	{"?", Q_MARK},
	{"[", MATRIX_BRAC_L},
	{"]", MATRIX_BRAC_R},
	{";", MATRIX_NL},
	{",", MATRIX_SEP},
};

// operators map
const std::map<std::string, int> OPERATORS_MAP = {
	{"+", OPERATOR_PLUS},
	{"-", OPERATOR_MINUS},
	{"*", OPERATOR_MULT},
	{"/", OPERATOR_DIV},
	{"=", OPERATOR_EQ},
	{"%", OPERATOR_MOD},
	{"^", OPERATOR_POW},
	{"**", OPERATOR_MAT_MULT},
};

// errors map
const std::map<int, std::string> ERRORS_MAP = {
	{FT_ERR_MISC, "FT_ERR_MISC"},
	{FT_ERR_NOT_FOUND, "FT_ERR_NOT_FOUND"},
	{FT_ERR_OK, "FT_ERR_OK"},
};
#endif  //!__CONSTANTS__H__
