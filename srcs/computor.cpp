#include "main.hpp"

void computor()
{
	// store command history here
	// store variables here

	while (true)
	{
		// Read line
		std::string line;
		

		std::cout << PROMPT;
		std::getline(std::cin, line);

		// exit command
		if (!std::cin || line == "exit") break ;

		// manage commands
		if (std::find(COMMANDS.begin(), COMMANDS.end(), line) != COMMANDS.end())
			std::cout << line << " is a command \n";
		else
		{
			// tokenize string
			tokenize(line);

			// parse tokens
		}
		
		// add to history

		
	}
	std::cout << "End\n";
}