#include "utils.h"

int	ft_isspace(int c);

int	ft_isspace(int c)
{
	return (c == ' ' || (unsigned int)c - '\t' < 5);
}
