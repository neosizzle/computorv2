#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "tokens.hpp"
#include "Base.hpp"
#include "constants.hpp"
#include "ft_error.hpp"
#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "Matrix.hpp"
#include "QMark.hpp"
#include "Parenthesis.hpp"
#include "Operator.hpp"
#include "Variable.hpp"
#include "ft_error.hpp"
#include "Function.hpp"

// ADD TYPE
/**
 * @brief Creates a list of typed value tokens
 * 
 * @param tokens 
 * @return std::vector<BaseAssignmentType *> 
 */
std::vector<BaseAssignmentType *> parse_tokens(std::vector<TokenBase> tokens)
{
	std::vector<BaseAssignmentType *> parsed_tokens;

	for (std::vector<TokenBase>::iterator iter = tokens.begin(); iter != tokens.end(); ++iter)
	{
		const TokenBase curr_token_base = *iter;

		// create new rational number type
		if (curr_token_base.type == N_RATIONAL)
		{
		parsed_tokens.push_back(curr_token_base.string.find('.') != std::string::npos ? new RationalNumber((float)atof(curr_token_base.string.c_str()))
			: new RationalNumber(atoi(curr_token_base.string.c_str())));
		}
		// craete new imaginery number type
		else if (curr_token_base.type == N_IMAGINARY)
		{
			// edge case for i
			if (curr_token_base.string == "i")
				parsed_tokens.push_back(new ImaginaryNumber(1));
			else
			{
				parsed_tokens.push_back(curr_token_base.string.find('.') != std::string::npos ? new ImaginaryNumber((float)atof(curr_token_base.string.c_str()))
							: new ImaginaryNumber(atoi(curr_token_base.string.c_str())));
			}
		}
		// create new matrix type
		else if (curr_token_base.type == N_MATRIX)
		{
		parsed_tokens.push_back(curr_token_base.string.find('.') != std::string::npos ? new Matrix(curr_token_base.string)
			: new Matrix(curr_token_base.string));
		}
		// create new operator type
		else if (OPERATORS_MAP.find(curr_token_base.string) != OPERATORS_MAP.end())
			parsed_tokens.push_back(new Operator(curr_token_base.string));
		// create new variable type
		else if (curr_token_base.type == VAR)
			parsed_tokens.push_back(new Variable(curr_token_base.string));
		// create parentheses type
		else if (curr_token_base.type == L_PARENTHESIS || curr_token_base.type == R_PARENTHESIS)
			parsed_tokens.push_back(new Parenthesis(curr_token_base.string));
		// create qmark type
		else if (curr_token_base.type == Q_MARK)
			parsed_tokens.push_back(new QMark());
		// create function type
		else if (curr_token_base.type == FUNC)
			parsed_tokens.push_back(new Function(curr_token_base.string));
		// others
		else
		{
			parsed_tokens.push_back(nullptr);
		}
	}
	return parsed_tokens;
}

/**
 * @brief Takes a string and splits them into tokens
 *
 * @param line
 */
std::vector<TokenBase> tokenize(std::string line)
{
	std::vector<TokenBase> tokens;

	// remove whitespaces
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());

	// loop through every character
	std::string::iterator line_iter = line.begin();
	while (line_iter != line.end())
	{
		const char CURR_CHAR = *line_iter;

		// check for **
		if (CURR_CHAR == '*' && *(line_iter + 1) == '*')
		{
			tokens.push_back({
				.type = OPERATOR_MAT_MULT,
				.string = "**"
			});
			line_iter += 2;
			continue;
		}

		// check for matrix
		if (CURR_CHAR == '[')
		{
			int bracket_stack;
			std::string::iterator mat_iter;

			bracket_stack = 1;
			mat_iter = line_iter + 1;
			while (mat_iter != line.end() && bracket_stack != 0)
			{
				if (*mat_iter == '[')
					++bracket_stack;
				else if (*mat_iter == ']')
					--bracket_stack;
				++mat_iter;
			}
			if (bracket_stack != 0) throw Ft_error("Invalid matrix brackets");
			const std::string mat_str = std::string(line_iter, mat_iter);
			tokens.push_back({
				.type = N_MATRIX,
				.string = mat_str
			});
			line_iter += mat_str.size();
			continue;
		}

		// check for lex tokens
		std::map<std::string, int>::const_iterator found_key_iter =
			LEX_TOKENS_MAP.find(std::string(1, CURR_CHAR));

		if (found_key_iter != LEX_TOKENS_MAP.end())
		{
			tokens.push_back({
				.type = found_key_iter->second,
				.string = std::string(1, CURR_CHAR)
			});

			// if next up its a -, insert a 0
			if (*(line_iter + 1) == '-')
			{
				tokens.push_back({
					.type = N_RATIONAL,
					.string = "0"
				});
			}
			
			++line_iter;
			continue;
		}

		// check for number if char isdigit
		if (isdigit(CURR_CHAR))
		{
			// extract number
			int is_imaginery;
			std::string::iterator num_iter;

			is_imaginery = 0;
			num_iter = line_iter;
			while (num_iter != line.end() && isdigit(*num_iter))
				++num_iter;

			if (*num_iter == '.')
			{
				++num_iter;
				while (num_iter != line.end() && isdigit(*num_iter))
					++num_iter;
			}

			if (*num_iter == 'i')
			{
				is_imaginery = 1;
				++num_iter;
			}

			const std::string num_str = std::string(line_iter, num_iter);
			tokens.push_back({
				.type = is_imaginery ? N_IMAGINARY : N_RATIONAL,
				.string = num_str
			});
			line_iter += num_str.size();
			continue;
		}

		// check for i
		if (CURR_CHAR == 'i')
		{
			tokens.push_back({
				.type = N_IMAGINARY,
				.string = "i"
			});
			++line_iter;
			continue;
		}

		// assume variable
		if (isalpha(CURR_CHAR))
		{
			int is_func;
			std::string var_str;

			is_func = 0;

			// extract var
			std::string::iterator var_iter = line_iter;

			while (var_iter != line.end() && isalpha(*var_iter))
				++var_iter;

			// check for function (brackets)
			if (*var_iter == '(')
			{
				while (var_iter != line.end() && *var_iter != ')')
					++var_iter;
				if (var_iter == line.end())
				{
					throw Ft_error("Invalid function syntax");
				}
				
				if (var_iter != line.end())
					++var_iter;
				is_func = 1;
			}

			var_str = std::string(line_iter, var_iter);

			// convert string to lowercase
			std::for_each(var_str.begin(), var_str.end(), [](char &c)
						  { c = ::tolower(c); });
			tokens.push_back({
				.type = is_func ? FUNC : VAR,
				.string = var_str
			});
			line_iter += var_str.size();
			continue;
		}
		throw Ft_error("tokenize: Invalid token");
		line_iter++;
	}

	// free form optimization
	std::vector<int> operator_types = {OPERATOR_DIV, OPERATOR_EQ, OPERATOR_MAT_MULT, OPERATOR_MINUS, OPERATOR_MOD, OPERATOR_MULT, OPERATOR_PLUS, OPERATOR_POW, Q_MARK, L_PARENTHESIS, R_PARENTHESIS};
	for (std::vector<TokenBase>::iterator i = tokens.begin(); i != tokens.end(); ++i)
	{
		const TokenBase token = *i;

		{
			// variable add *
			if (i != tokens.begin() && token.type == VAR && std::find(operator_types.begin(), operator_types.end(), (*(i - 1)).type) == operator_types.end())
				i = tokens.insert(i, {.type = OPERATOR_MULT, .string = "*"});
			else if (i + 1 != tokens.end() && token.type == VAR && std::find(operator_types.begin(), operator_types.end(), (*(i + 1)).type) == operator_types.end())
				i = tokens.insert(i + 1, {.type = OPERATOR_MULT, .string = "*"});

			// left parenthesis add *
			if (i != tokens.begin() && token.type == L_PARENTHESIS && std::find(operator_types.begin(), operator_types.end(), (*(i - 1)).type) == operator_types.end())
				i = tokens.insert(i, {.type = OPERATOR_MULT, .string = "*"});

			// right parenthesis add *
			if (i + 1 != tokens.end() && token.type == R_PARENTHESIS && std::find(operator_types.begin(), operator_types.end(), (*(i + 1)).type) == operator_types.end())
				i = tokens.insert(i + 1, {.type = OPERATOR_MULT, .string = "*"});
		}
	}

	// // edge case for a = -n
	// if (tokens.size() > 2)
	// {
	// 	if (tokens[1].type == OPERATOR_EQ && tokens[2].type == OPERATOR_MINUS)
	// 		tokens.insert(tokens.begin() + 2, {.type = N_RATIONAL, .string = "0"});
	// }
	

	return tokens;
}