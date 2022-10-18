#include "libraries.hpp"
#include "constants.hpp"
#include "tokens.hpp"

// Computor
void	computor();

// tokens
std::vector<TokenBase>	tokenize(std::string line);
void	parse_tokens(std::vector<TokenBase> tokens);

// utils
float ft_pow(float a, int power);


// logging
void	print_unparsed_tokens(std::vector<TokenBase> tokens);