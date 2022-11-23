#ifndef __POLYNOMIAL__H__
#define __POLYNOMIAL__H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include "ft_error.hpp"

/**
 * @brief Representation of a term
 *
 */
class Term
{
public:
	float constant;
	int power;
	bool is_neg;
};

/**
 * @brief Representation of a solution
 *
 */
class Solution
{
public:
	float solution_one;
	float solution_two;
	float imaginary_term;
	float imaginary_coefficient;
	int num_sols;
	bool neg_discriminant;
	int for_degree;
};

/**
 * @brief Representation of a dinomial equation
 *
 */
class DinobialEquation
{
public:
	float a;
	float b;
	float c;
};

/** global consts **/
const char EQ_SYMBOL = '=';
const char KARET_SYMBOL = '^';
const std::vector<char> POLY_LINK_SYMBOLS = {'+', '-'};

/**global vars**/
extern char VAR_SYMBOL;
extern std::vector<char> TERM_SYMBOLS;

/**
 * @brief Math utils
 *
 */
int ft_abs(int a, int b);
float ft_sqrt(float x, float guess);
float ft_pow(float a, int power);
Solution evaluate_equation(std::vector<Term> terms);

/**
 * @brief Utils
 *
 */
bool compare_powers(Term one, Term two);
int count_digit(int number);

/**
 * @brief Term operations
 *
 */
char validate_symbols(std::string str);
void extract_terms(std::string str, std::vector<Term> &terms);
void print_terms(std::vector<Term> terms);
void simplify_terms(std::vector<Term> &terms);
int validate_equation(std::vector<Term> terms);
std::string terms_to_str(std::vector<Term> terms);

/**
 * @brief Print functions
 *
 */
std::string solution_to_str(Solution sol);
// void print_err(std::string message);
// void print(std::string message);

std::string compute_polynomial(std::string input);
#endif  //!__POLYNOMIAL__H__
