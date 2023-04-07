#include "polynomial.hpp"

std::string solution_to_str(Solution sol)
{
	std::string res;

	// print all possible solutions
	if (sol.all_interger_solution && sol.for_degree == 0)
	{
		res += (std::string(BOLDWHITE) + std::string("Number of solutions: " )+ std::string(RESET) + "All integers");
		return res;
	}
	else if (!sol.all_interger_solution && sol.for_degree == 0)
	{
		res += (std::string(BOLDWHITE) + std::string("Number of solutions: " )+ std::string(RESET) + "Impossible");
		return res;
	}

	// print number of solutions
	res += std::string(BOLDWHITE) + std::string("Number of solutions: " )+ std::string(RESET) + std::to_string(sol.num_sols) + "\n";

	// positive discriminant
	if (sol.neg_discriminant == false)
	{
		// print positive discriminant
		if (sol.for_degree == 2)
			res += std::string(BOLDWHITE) + std::string("Dissciminant " )+ std::string(RESET) + "Positive\n";

		// print solution one
		res += std::string(BOLDWHITE) + std::string("Solution one: " )+ std::string(RESET) + std::to_string(sol.solution_one) + "\n";

		// if num of sols is 2, print solution 2
		if (sol.num_sols == 2)
			res += std::string(BOLDWHITE) + std::string("Solution two: " )+ std::string(RESET) + std::to_string(sol.solution_two) + "\n";
	}
	else
	{
		// print positive discriminant
		res += (std::string(BOLDWHITE) + std::string("Dissciminant " )+ std::string(RESET) + "Negative\n");


		// print solution one
		res += (std::string(BOLDWHITE) + std::string("Solution one: " )+ std::string(RESET) + std::to_string(sol.imaginary_coefficient) + std::string("+") + std::to_string(sol.imaginary_term) + "i\n");

		// if num of sols is 2, print solution 2
		if (sol.num_sols == 2)
			res += (std::string(BOLDWHITE) + std::string("Solution two: " )+ std::string(RESET) + std::to_string(sol.imaginary_coefficient) + std::string("-") + std::to_string(sol.imaginary_term) + "i\n");
	}
	return res;
}
