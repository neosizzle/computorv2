#include "main.hpp"

/**
 * @brief Evaluates the of number a raised by the power of power
 * 
 * @param a 
 * @param power 
 * @return double 
 */
float ft_pow(float a, int power)
{
	if (power == 0)
		return 1;
	if (power == 1)
		return a;
	if (power < 0)
		return 0;
	return (ft_pow((a * a), power - 1));
}
