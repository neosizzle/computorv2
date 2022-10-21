#include "main.hpp"

void computor()
{
	// history (command, result)
	std::map<std::string, std::string> history;

	// variables (variablename, variable type with values and stuff)
	std::map<std::string, BaseAssignmentType *> variables;

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
			// tokenize string parse tokens
			std::vector<BaseAssignmentType *> tokens;

			tokens = parse_tokens(tokenize(line));
			print_parsed_tokens(tokens);

			// expand variables
			try
			{
				expand_variables(tokens, variables);
			}
			catch(const Ft_error &e)
			{
				// free tokens

				ft_perror(e);
				continue ;
			}
			
			// see if last token is a qmark

			// validate tokens

			// do evaluation

			// assign or display result

			// free tokens
		}
		

		// add history for rl
		add_history(rl_buff);

		// add history for computor

		free(rl_buff);
	}
	
	// free variables
	std::cout << "End\n";
}