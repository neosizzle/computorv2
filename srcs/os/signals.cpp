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
	if (!signal) return;
	std::cout << "\n";
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}