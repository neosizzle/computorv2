#include "computor.hpp"

void computor()
{
	// history (command, result)
	std::map<std::string, std::string> history;

	// variables (variablename, variable type with values and stuff)
	std::map<std::string, BaseAssignmentType *> variables;

	std::string res_str;

	while (true)
	{
		char 		*rl_buff; // line buffer
		std::string  line; // line cpp
		bool		 is_compute_action; // is this action a compute action or assign action

		is_compute_action = false;
		rl_buff = readline(PROMPT.c_str());
		if (rl_buff == NULL)
		{
			free(rl_buff);
			break ;
		}
		line = std::string(rl_buff);

		// exit command
		if (line == "exit")
		{
			free(rl_buff) ;
			break ;
		}

		// manage commands
		if (std::find(COMMANDS.begin(), COMMANDS.end(), line) != COMMANDS.end())
			handle_builtin(line, history, variables);
		else
		{
			// tokenize string parse tokens
			std::vector<BaseAssignmentType *> tokens;

			tokens = parse_tokens(tokenize(line));

			// determine if last token is qmark
			if(tokens.size() > 1 && tokens.back()->getType() == Q_MARK )
				is_compute_action = true;

			try
			{
				// expand variables
				expand_variables(tokens, variables, is_compute_action);

				// validate tokens
				validate_tokens(tokens, is_compute_action);

				// evaluate and print result
				res_str = evalaute(tokens, is_compute_action, variables);
				std::cout << res_str << "\n";

				// add history for computor
				history.insert({line, res_str});
			}
			catch(const Ft_error &e)
			{
				free_tokens(tokens);
				ft_perror(e);
				add_history(rl_buff);
				free(rl_buff);
				continue ;
			}
			catch (const std::runtime_error& e)
			{
				free_tokens(tokens);
				free(rl_buff);
				std::cerr << "Runtime err: " << e.what();
				continue;
			}
			
			// free tokens
			free_tokens(tokens);
		}
		
		// add history for rl
		add_history(rl_buff);

		free(rl_buff);
	}
	
	// free variables
	free_variables(variables);
	std::cout << "End\n";
}