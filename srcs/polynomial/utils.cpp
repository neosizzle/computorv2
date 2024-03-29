#include "polynomial.hpp"

/**
 * @brief validate input to have only digits, allowed symbols and x.
 *
 * @param str string to validate
 * @return char bad symbol if not valid, 0 otherwise
 */
char validate_symbols(std::string str)
{
	// validate input to have only digits, allowed symbols and x.
	for (std::string::iterator iter = str.begin(); iter != str.end(); iter++)
	{
		char curr = *iter;
		if (!isdigit(curr)
			&& curr != '.'
			&& curr != EQ_SYMBOL
			&& std::find(TERM_SYMBOLS.begin(), TERM_SYMBOLS.end(), *iter) == TERM_SYMBOLS.end()
			&& std::find(POLY_LINK_SYMBOLS.begin(), POLY_LINK_SYMBOLS.end(), *iter) == POLY_LINK_SYMBOLS.end())
			return curr;
	}

	return 0;
}

/**
 * @brief Count how many digit in a number
 * assumes no prefixes
 * 
 * @param str 
 * @return int 
 */
int scount_digit(const char *str)
{
	int count = 0;
	
	while (*str 
	&& (isdigit(*str) || *str == '.'))
	{
		++count;
		++str;
	}

	return count;
}