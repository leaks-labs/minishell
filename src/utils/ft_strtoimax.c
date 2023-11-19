#include "utils.h"

intmax_t	ft_strtoimax(const char *str, bool *error);

intmax_t	ft_strtoimax(const char *str, bool *error)
{
	const uintmax_t	intmax_max = INTMAX_MAX;
	uintmax_t		n;
	int				sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*str) != 0)
		++str;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	*error = (ft_isdigit(*str) != 1);
	while (*error == false && ft_isdigit(*str) != 0)
	{
		n = n * 10 + (uintmax_t)(*str++) - '0';
		if ((sign > 0 && n > intmax_max) \
			|| (sign < 0 && n > intmax_max + 1))
			*error = true;
	}
	while (ft_isspace(*str) != 0)
		++str;
	if (*str != '\0')
		*error = true;
	return ((intmax_t)n * (intmax_t)sign);
}
