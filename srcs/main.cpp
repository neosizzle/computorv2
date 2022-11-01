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
	ImaginaryNumber test;
	test.real_part = RationalNumber(5);
	test.imaginary_part = RationalNumber(4);
	test.power = 5;

	RationalNumber test2 = (69);

	ImaginaryNumber simplified;
	simplified = test2 + test;
	std::cout << "real part: " << simplified.real_part.toString() << "\n";
	std::cout << "i part: " << simplified.imaginary_part.toString() << "\n";
	std::cout << "pow: " << std::to_string(simplified.power) << "\n";
}