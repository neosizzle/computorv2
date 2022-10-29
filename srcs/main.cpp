#include "main.hpp"

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
	// computor();
	RationalNumber test(12);
	ImaginaryNumber test2(12);
	std::cout << test + "wutt" << "\n";
}