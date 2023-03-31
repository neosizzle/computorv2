#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <iostream>

/**
 * @brief Handles sigint
 * 
 * @param signal 
 */
void sigint_handler(int signal)
{
	
	std::cout << signal << "\n";
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}