#include "polynomial.hpp"
#include "ft_error.hpp"

char VAR_SYMBOL;
std::vector<char> TERM_SYMBOLS;
std::string compute_polynomial(std::string arg)
{
	std::vector<Term> terms;

	// trim all whitespaces from input
	arg.erase(std::remove_if(arg.begin(), arg.end(), isspace), arg.end());

	// extract var symbol
	VAR_SYMBOL = 'x';
	TERM_SYMBOLS = {'^', '*'};
	for (size_t i = 0; i < arg.size(); ++i)
	{
		if (isalpha(arg[i]))
		{
			VAR_SYMBOL = arg[i];
			break;
		} 
	}
	TERM_SYMBOLS.push_back(VAR_SYMBOL);
	

	// validate symbols
	const char invalid_symbol = validate_symbols(arg);
	if (invalid_symbol)
		throw Ft_error(std::string("Invalid symbol \'") + invalid_symbol + std::string("\'"));

	// can only have one '='
	if (std::count(arg.begin(), arg.end(), '=') != 1)
		throw Ft_error(std::string("Invalid number of  \'") + EQ_SYMBOL + std::string("\'"));

	// extract and group terms
	extract_terms(arg, terms);

	// simplufy terms
	simplify_terms(terms);

	// validate equation
	if (validate_equation(terms))
		throw Ft_error("Equation not valid");

	const Solution solution = evaluate_equation(terms);
	// print_solution(solutipon);
	return solution_to_str(solution);
}