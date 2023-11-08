#include "utils.h"

int	ft_isalnum(int c);

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) == true || ft_isdigit(c) == true);
}
