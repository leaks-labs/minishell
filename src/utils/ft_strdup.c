#include "utils.h"

char	*ft_strdup(const char *s1);

char	*ft_strdup(const char *s1)
{
	const size_t	size = ft_strlen(s1);
	char			*s2;

	s2 = ft_calloc(size + 1, sizeof(char));
	if (s2 != NULL)
		ft_memcpy(s2, s1, size + 1);
	return (s2);
}
