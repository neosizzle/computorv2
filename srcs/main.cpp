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

	try
	{
		Matrix mat("[[1,2,3];[4,5,6]]");
		Matrix mat2("[[7,8];[9,10];[11,12]]");
		BaseAssignmentType *matres = mat.mult(&mat2);

		if (matres == nullptr) std::cout << "null\n";
		else std::cout << matres->toString() << "\n";
		free_token(matres);
		}
		catch(Ft_error e)
		{
			std::cerr << e << '\n';
	}
	

	// computor();
}