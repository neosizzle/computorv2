#include "main.hpp"

void	tokenize(std::string line)
{
	std::vector<TokenBase> tokens;

	// remove whitespaces
	line.erase( std::remove( line.begin(), line.end(), ' ' ), line.end());
	line.erase( std::remove( line.begin(), line.end(), '\t' ), line.end());

	// loop throu hcharacter by character
	std::string::iterator line_iter = line.begin();
	while (line_iter != line.end())
	{
		const char CURR_CHAR = *line_iter;
		// std::cout << CURR_CHAR << "\n";

		// check for **
		if (CURR_CHAR == '*' && *(line_iter + 1) == '*')
		{
			tokens.push_back({
				type : OPERATOR_MAT_MULT,
				string : "**"
			});
			line_iter += 2;
			continue ;
		}

		// check for imaginary symbol

		// check for lex tokens
		std::map<std::string, int>::const_iterator found_key_iter =
		LEX_TOKENS_MAP.find(std::string(1, CURR_CHAR));

		if (found_key_iter != LEX_TOKENS_MAP.end())
		{
			tokens.push_back({
				type : found_key_iter->second,
				string : std::string(1, CURR_CHAR)
			});
			++line_iter;
			continue ;
		}

		// check for functions
		// if (std::string(line_iter, line.end()).rfind(""))

		// check for number if char isdigit
		if (isdigit(CURR_CHAR))
		{
			// extract number
			int					  is_imaginery;
			std::string::iterator num_iter = line_iter;

			is_imaginery = 0;
			while (num_iter != line.end() && isdigit(*num_iter)) ++num_iter;

			if (*num_iter == '.')
			{
				++num_iter;
				while (num_iter != line.end() && isdigit(*num_iter)) ++num_iter;
			}
			
			if (*num_iter == 'i')
			{
				is_imaginery = 1;
				++num_iter;
			}

			const std::string num_str = std::string(line_iter, num_iter);
			tokens.push_back({
				type : is_imaginery ? N_IMAGINARY : N_RATIONAL,
				string : num_str
			});
			line_iter += num_str.size();
			continue ;
		}

		// assume variable
		if (isalpha(CURR_CHAR))
		{
			// extract var
			std::string::iterator var_iter = line_iter;

			while (var_iter != line.end() && isalpha(*var_iter)) ++var_iter;

			const std::string var_str = std::string(line_iter, var_iter);
			tokens.push_back({
				type : VAR,
				string : var_str
			});
			line_iter += var_str.size();
			continue ;
		} 
		std::cout << "it didnt hit anything\n";
		line_iter++;
	}
	
	std::cout << "tokens: \n";
	for (std::vector<TokenBase>::iterator i = tokens.begin(); i != tokens.end(); i++)
		std::cout << i->string << "\n";
	
}