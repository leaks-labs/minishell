#include "utils.h"

char		*ft_strdup(const char *s1);

char	*ft_strdup(const char *s1)
{
	const size_t	size = ft_strlen(s1);
	char			*s2;

	s2 = ft_calloc(size + 1, sizeof(*s2));
	if (s2 == NULL)
		return (NULL);
	return (ft_memcpy(s2, s1, size + 1));
}
