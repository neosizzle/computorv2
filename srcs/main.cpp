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

	ImaginaryNumber test2;
	test2.real_part = RationalNumber(3);
	test2.imaginary_part = RationalNumber(4);
	test2.power = 1;

	ImaginaryNumber simplified;
	simplified = test / test;
	std::cout << "real part: " << simplified.real_part.toString() << "\n";
	std::cout << "i part: " << simplified.imaginary_part.toString() << "\n";
	std::cout << "pow: " << std::to_string(simplified.power) << "\n";
}