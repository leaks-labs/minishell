#include "utils.h"

int	ft_isdigit(int c);

int	ft_isdigit(int c)
{
	return ((unsigned int)c - '0' < 10);
}
