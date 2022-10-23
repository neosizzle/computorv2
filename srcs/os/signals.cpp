#include "libraries.hpp"

/**
 * @brief Handles sigint
 * 
 * @param signal 
 */
void sigint_handler(int signal)
{
	std::cout << "\n";
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}