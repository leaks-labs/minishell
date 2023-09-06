#include "utils.h"

size_t	ft_strlen(const char *s);

size_t	ft_strlen(const char *s)
{
	const char	*ptr;

	ptr = s;
	while (*ptr != '\0' )
		++ptr;
	return ((size_t)(ptr - s));
}
