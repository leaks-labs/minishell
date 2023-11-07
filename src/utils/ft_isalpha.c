#include "utils.h"

int	ft_isalpha(int c);

int	ft_isalpha(int c)
{
	return (((unsigned int)c | 32) - 'a' < 26);
}
