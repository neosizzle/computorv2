#include <iostream>
#include <map>
#include "Base.hpp"

void	handle_builtin(std::string line, std::map<std::string, std::string> history, std::map<std::string, BaseAssignmentType *> variables)
{
	if (line == "list")
	{
		std::map<std::string, BaseAssignmentType *>::iterator variables_iter;

		variables_iter = variables.begin();
		while (variables_iter != variables.end())
		{
			std::cout << (*variables_iter).first << " = " << (*variables_iter).second->toString() << "\n";
			variables_iter++;
		}
	}
	else if (line == "history")
	{
		std::map<std::string, std::string>::iterator history_iter;

		history_iter = history.begin();
		while (history_iter != history.end())
		{
			std::cout << (*history_iter).first << "\n" << (*history_iter).second << "\n\n";
			history_iter++;
		}
	}
}