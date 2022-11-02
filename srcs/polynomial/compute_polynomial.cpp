#include "polynomial.hpp"
#include "ft_error.hpp"

std::string compute_polynomial(std::string arg)
{
	std::vector<Term> terms;

	std::cout << "arg "<< arg << "\n";
	// trim all whitespaces from input
	arg.erase(std::remove_if(arg.begin(), arg.end(), isspace), arg.end());

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