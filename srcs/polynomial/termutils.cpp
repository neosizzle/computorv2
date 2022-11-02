#include "polynomial.hpp"


/**
 * @brief Compares two terms by their powers
 *
 */
bool compare_powers(Term one, Term two)
{
	return one.power > two.power;
}

/**
 * @brief Convert terms to equation string
 * 
 * @param terms 
 * @return std::string 
 */
std::string terms_to_str(std::vector<Term> terms)
{
	std::string res;
	std::ostringstream ss;

	for (std::vector<Term>::iterator iter = terms.begin(); iter != terms.end(); ++iter)
	{
		const Term curr_term = *iter;

		// decide wether to print + or not for positive terms
		if (curr_term.is_neg)
			ss << "- ";
		else if (iter != terms.begin())
			ss << "+ ";

		// print constant
		if (curr_term.constant == 0)
		{
			ss <<  '0';
			continue;
		}
		ss << curr_term.constant;

		// print variable
		ss << VAR_SYMBOL;

		// print power
		ss << KARET_SYMBOL;
		ss << curr_term.power;
		ss << ' ';
	}
	res = ss.str();
	return res;
}

/**
 * @brief Prints out terms in a polynomial standard
 *
 * @param terms
 */
void print_terms(std::vector<Term> terms)
{
	for (std::vector<Term>::iterator iter = terms.begin(); iter != terms.end(); ++iter)
	{
		const Term curr_term = *iter;

		// decide wether to print + or not for positive terms
		if (curr_term.is_neg)
			std::cout << '-';
		else if (iter != terms.begin())
			std::cout << '+';

		// print constant
		if (curr_term.constant == 0)
		{
			std::cout << '0';
			continue;
		}
		std::cout << curr_term.constant;

		// print variable
		std::cout << VAR_SYMBOL;

		// print power
		std::cout << KARET_SYMBOL << curr_term.power;
	}
	std::cout << "\n";
}

/**
 * @brief print a single term
 * 
 * @param term 
 */
void print_term(Term curr_term)
{
		// decide wether to print + or not for positive terms
		if (curr_term.is_neg)
			std::cout << '-';

		// print constant
		if (curr_term.constant == 0)
		{
			std::cout << '0';
			return ;
		}
		std::cout << curr_term.constant;

		// print variable
		std::cout << VAR_SYMBOL;

		// print power
		std::cout << KARET_SYMBOL << curr_term.power << "\n";
}

/**
 * @brief Parses term string into term struct
 *
 * @param term_str
 * @return Term
 */
Term parse_term(std::string term_str)
{
	Term res;
	int read_idx;
	int constant;
	int power;
	int is_neg;
	int const_is_var;

	read_idx = 0;
	const_is_var = 0;
	power = 0;
	is_neg = false;

	// look for '-'
	if (term_str[read_idx] == '-')
	{
		is_neg = true;
		++read_idx;
	}

	// look for '+'
	if (term_str[read_idx] == '+')
		++read_idx;

	// obtain constant value
	if (term_str[read_idx] == VAR_SYMBOL)
	{
		constant = 1;
		const_is_var = 1;
	}
	else
		constant = atoi(term_str.c_str() + read_idx);

	// increm read idx
	read_idx += count_digit(constant);

	// if '*' is found, increm read index so it points to variable
	if (term_str[read_idx] == '*')
		++read_idx;

	// if a karet is found, record power
	if (term_str.length() > 2 &&  term_str[read_idx + 1] == '^')
		power = atoi(term_str.c_str() + (read_idx + 2));
	// case where const is the variable itself
	else if (const_is_var)
	{
		power = atoi(term_str.c_str() + (read_idx + 1));
		if (!power)
			++power;
	}
	// case wherer const(variable)
	else if (term_str[read_idx] == VAR_SYMBOL)
		power = 1;
	else
		power = 0;

	res.is_neg = is_neg;
	res.power = power;
	res.constant = constant;
	return res;
}

/**
 * @brief Check if current term is a valid term before passing it to parser
 *
 * @param term_str term to validate
 * @return int 1 if not valid, 0 otherwise
 */
int validate_term(std::string term_str)
{
	// check for sole '+' and '-'
	if (term_str == "+" || term_str == "-")
		return 1;

	// can only have 1 or 0 '*'
	if (std::count(term_str.begin(), term_str.end(), '*') > 1)
		return 1;

	const int MULT_IDX = term_str.find('*');

	if (MULT_IDX != std::string::npos)
	{

		// '*' must not be first or last char
		if (MULT_IDX == 0 || MULT_IDX == term_str.length() - 1)
			return 1;

		// '*' must be followed by the variable and must be predeceased by constant
		if (term_str[MULT_IDX + 1] != VAR_SYMBOL)
			return 1;

		if (!isdigit(term_str[MULT_IDX - 1]))
			return 1;
	}

	const int VAR_IDX = term_str.find(VAR_SYMBOL);
	if (VAR_IDX != std::string::npos)
	{
		// 'x' must not be followed by the variable and must only be predeceased by '^'
		if (VAR_IDX == term_str.length() - 2 && term_str[VAR_IDX + 1] != '^')
			return 1;

		if (VAR_IDX > 0 && term_str[VAR_IDX - 1] == VAR_SYMBOL)
			return 1;
	}

	const int KARET_IDX = term_str.find(KARET_SYMBOL);
	if (KARET_IDX != std::string::npos)
	{
		// '^' must be followed by a variable
		if (term_str[KARET_IDX - 1] != VAR_SYMBOL)
			return 1;

		// after '^' must have digit
		if (!isdigit(term_str[KARET_IDX + 1]))
			return 1;

		// power must be less than 3 and more than -1
		const int power = atoi(term_str.c_str() + KARET_IDX + 1);
		if (power > 2 || power < 0)
			return 1;
	}

	return 0;
}

/**
 * @brief Groups all terms to the left hand side without simplification
 * 
 * @param lhs 
 * @param rhs 
 */
void group_terms(std::vector<Term> &lhs, std::vector<Term> &rhs)
{

	for (std::vector<Term>::iterator rhs_iter = rhs.begin(); rhs_iter != rhs.end(); ++rhs_iter)
	{
		Term curr;

		curr = *rhs_iter;
		curr.is_neg = !curr.is_neg;
		lhs.push_back(curr);
	}
}

/**
 * @brief Simplify terms in an equation to make the form ax^2+bx+c (assume terms are sorted by power)
 * 
 * @param terms 
 */
void simplify_terms(std::vector<Term> &terms)
{
	std::vector<Term> new_terms;
	Term new_term;
	int curr_power;

	curr_power = INT16_MAX;
	new_term.constant = 0;
	new_term.is_neg = false;
	for ( std::vector<Term>::iterator iter = terms.begin(); iter != terms.end(); ++iter)
	{
		Term curr_term = *iter;

		// current iter term is not equals to current power
		if (curr_term.power != curr_power)
		{
			// push new term to terms if new term is not initial
			if (curr_power != INT16_MAX)
				new_terms.push_back(new_term);
			curr_power = curr_term.power;
			new_term.power = curr_term.power;
			new_term.constant = curr_term.constant;
			new_term.is_neg = curr_term.is_neg ;
		}
		else
		{
			// current iter term is same power as curr new ter
			if (new_term.is_neg)
			{
				// new term is negative 
				// curr iter term is negative
				if (curr_term.is_neg)
				{
					new_term.constant += curr_term.constant;
				}
				else
				{
					// curr iter term is positive
					if (curr_term.constant > new_term.constant) new_term.is_neg = false;
					new_term.constant = (float)ft_abs(new_term.constant, curr_term.constant);
				}

			}
			else
			{
				// new term is positive
				// curr iter term is negative
				if (curr_term.is_neg)
				{
					if (curr_term.constant > new_term.constant) new_term.is_neg = true;
					new_term.constant = (float)ft_abs(new_term.constant, curr_term.constant);
				}
				else
					new_term.constant += curr_term.constant;
			}
		}
	}
	
	//add last term
	if (curr_power != INT16_MAX)
		new_terms.push_back(new_term);

	// override term
	terms = new_terms;
}

/**
 * @brief Extract and group terms based on arg input
 * 
 * @param str 
 * @param terms 
 */
void extract_terms(std::string str, std::vector<Term> &terms)
{
	int read_start;
	int read_end;
	std::string curr_term_str;
	char curr;

	read_start = 0;
	read_end = 1;

	// read until '=' is found (LHS)
	while (str[read_start] != EQ_SYMBOL)
	{
		read_end = read_start + 1;

		while (read_end < str.length())
		{
			curr = str[read_end];
			if (std::find(POLY_LINK_SYMBOLS.begin(), POLY_LINK_SYMBOLS.end(), curr) != POLY_LINK_SYMBOLS.end() || curr == EQ_SYMBOL)
			{
				curr_term_str = str.substr(read_start, read_end - read_start);
				// return 1 here
				if (validate_term(curr_term_str))
				{
					throw Ft_error(std::string( "Polynomial Bad token: ") + curr_term_str);
					exit(1);
				}

				// push to term array
				const Term term = parse_term(curr_term_str);
				terms.push_back(term);
				break;
			}
			++read_end;
		}
		read_start = read_end;
	}

	// read until end of string (RHS)
	++read_start;
	std::vector<Term> rhs_terms;
	while (str[read_start] != 0)
	{
		read_end = read_start + 1;

		while (read_end < str.length() + 1)
		{
			curr = str[read_end];
			if (std::find(POLY_LINK_SYMBOLS.begin(), POLY_LINK_SYMBOLS.end(), curr) != POLY_LINK_SYMBOLS.end() || curr == 0)
			{
				curr_term_str = str.substr(read_start, read_end - read_start);
				// return 1 here
				if (validate_term(curr_term_str))
				{
					throw Ft_error(std::string( "Bad token: ") + curr_term_str);
					exit(1);
				}

				// push to term array
				const Term term = parse_term(curr_term_str);
				rhs_terms.push_back(term);
				break;
			}
			++read_end;
		}
		read_start = read_end;
	}

	// move rhs to lhs (group terms)
	group_terms(terms, rhs_terms);
	// print_terms(rhs_terms);

	// sort terms by power
	std::sort(terms.begin(), terms.end(), compare_powers);
}

//validates the equatuion to make sure its a valid 2nd degree polynimial (assumes terms are sorted by power)
int validate_equation(std::vector<Term> terms)
{
	// print degree
	std::cout << std::string(BOLDWHITE) + std::string("Degree: ") + std::string(RESET) + std::to_string(terms[0].power) << "\n";

	// check if max power is 2
	if (terms[0].power > 2)
	{
		throw Ft_error("Degree must not be more than 2");
		return 1;
	}

	// check if min power is 1
	if (terms[0].power <= 0)
	{
		throw Ft_error("Degree must be greater than 0");
		return 1;
	}
	// check if num of terms is more than 3
	// if (terms.size() > 3)
	// {
	// 	std::cout << "Bad number of terms\n";
	// 	return 1;
	// }

	// all good
	return 0;
}