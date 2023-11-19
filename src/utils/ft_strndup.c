#include "utils.h"

char	*ft_strndup(const char *s1, size_t n);

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	size;
	char	*s2;

	size = ft_strlen(s1);
	if (n < size)
		size = n;
	s2 = ft_calloc(size + 1, sizeof(char));
	if (s2 != NULL)
		ft_memcpy(s2, s1, size);
	return (s2);
}
