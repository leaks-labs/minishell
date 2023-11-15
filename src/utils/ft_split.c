#include "utils.h"

char			**ft_split(const char *str, const char sep);
static size_t	ft_count_words(const char *str, const char sep);
static char		**ft_write_words(const char *str, const char sep, char **tab);

char	**ft_split(const char *str, const char sep)
{
	char	**tab;
	size_t	n_words;

	if (str == NULL)
		return (NULL);
	n_words = ft_count_words(str, sep);
	tab = ft_calloc(n_words + 1, sizeof(char *));
	if (tab != NULL)
		tab = ft_write_words(str, sep, tab);
	return (tab);
}

static size_t	ft_count_words(const char *str, const char sep)
{
	size_t	n_words;

	n_words = 0;
	while (*str != '\0')
	{
		if (*str == sep)
			++str;
		else
		{
			++n_words;
			while (*str != '\0' && *str != sep)
				++str;
		}
	}
	return (n_words);
}

static char	**ft_write_words(const char *str, const char sep, char **tab)
{
	char	**cpytab;
	size_t	len;

	cpytab = tab;
	while (*str != '\0')
	{
		while (*str != '\0' && *str == sep)
			++str;
		len = 0;
		while (str[len] != '\0' && str[len] != sep)
			++len;
		*tab = ft_substr(str, 0, len);
		str += len;
		if (*tab == NULL)
			return (ft_freef("%P", cpytab));
		++tab;
	}
	return (cpytab);
}
