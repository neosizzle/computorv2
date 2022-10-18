#include "main.hpp"

void computor()
{
	// store command history here
	// store variables here

	while (true)
	{
		char 		*rl_buff;
		std::string  line;

		rl_buff = readline(PROMPT.c_str());
		if (rl_buff == NULL)
		{
			free(rl_buff);
			break ;
		}
		line = std::string(rl_buff);

		// exit command
		if (line == "exit") break ;

		// manage commands
		if (std::find(COMMANDS.begin(), COMMANDS.end(), line) != COMMANDS.end())
			std::cout << line << " is a command \n";
		else
		{
			// tokenize string
			

			// parse tokens
			parse_tokens(tokenize(line));
			
		}
		

		// add history for rl
		add_history(rl_buff);

		// add history for computor

		free(rl_buff);
	}
	
	std::cout << "End\n";
}