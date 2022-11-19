#include "main.hpp"
#include <csignal>
#include <iostream>
#include "Function.hpp"
#include "RationalNum.hpp"
#include "constants.hpp"
#include "Operator.hpp"
#include "Variable.hpp"
#include "Base.hpp"

void	free_token(BaseAssignmentType * tokens);

void	test_func(Function func)
{
	// std::cout << func.toString() << "\n";
	BaseAssignmentType *ans;

	ans = func.evaluate_image();
	std::cout << ans->toString() << "\n";
	free_token(ans);
}

int main(int argc, char** argv)
{
	(void) argv;

	// install signal handler
	std::signal(SIGINT, sigint_handler);

	if (argc != 1)
	{
		std::cout << "Usage: ./computor\n";
		return 1;
	}
	
	RationalNumber * two = new RationalNumber(2);
	Variable * x = new Variable("x");
	Operator *plus = new Operator("+");
	std::vector<BaseAssignmentType *> tokens;
	tokens.push_back(two);
	tokens.push_back(plus);
	tokens.push_back(x);
	
	Function func(tokens, x, "func");
	func.set_object(two);
	test_func(func);
	free_token(two);
	free_token(plus);
	free_token(x);
	// computor();
}