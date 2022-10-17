#include "main.hpp"

int main(int argc, char** argv)
{
	(void) argv;
	if (argc != 1)
	{
		std::cout << "Usage: ./computor\n";
		return 1;
	}
	computor();
}