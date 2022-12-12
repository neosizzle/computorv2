#include "main.hpp"
#include <csignal>
#include <iostream>

#include "Function.hpp"
#include "RationalNum.hpp"
#include "constants.hpp"
#include "Operator.hpp"
#include "Variable.hpp"
#include "Base.hpp"
#include "Matrix.hpp"
#include "ImaginaryNum.hpp"
#include "ft_error.hpp"

void	free_token(BaseAssignmentType * tokens);
void	free_tokens(std::vector<BaseAssignmentType *> tokens);
void print_parsed_tokens_no_format(std::vector<BaseAssignmentType *> tokens);

void	test_func(Function func)
{
	std::cout << func.toString() << "\n";
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

	// try
	// {
	// 	Matrix mat("[[13,26];[39,13]]");
	// 	Matrix mat2("[[7,4];[2,3]]");
	// 	RationalNumber two(2);
	// 	BaseAssignmentType *matres = two.div(&mat2);

	// 	// std::cout << matres.toString() << "\n";
	// 	if (matres != nullptr)
	// 	{
	// 		std::cout << matres->toString() << "\n";
	// 		free_token(matres);
	// 	}
	// 	else
	// 		std::cout << "null\n";
	// }
	// catch(Ft_error e)
	// {
	// 	std::cerr << e << '\n';
	// }
	

	computor();
}