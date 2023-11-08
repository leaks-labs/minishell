#include "utils.h"

char	*ft_strchr(const char *s, int c);

char	*ft_strchr(const char *s, int c)
{
	const char	c2 = (const char)c;

	if (c2 == '\0')
		return ((char *)s + ft_strlen(s));
	while (*s != c2)
		if (*s++ == '\0')
			return (NULL);
	return ((char *)s);
}
