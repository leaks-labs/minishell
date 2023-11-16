#include "utils.h"

void	ft_rm_quotes(char *del);

void	ft_rm_quotes(char *del)
{
	char	to_trim;
	size_t	i;
	size_t	j;

	to_trim = '\0';
	i = 0;
	j = i;
	while (del[i] != '\0')
	{
		if (to_trim == '\0' && (del[i] == '\"' || del[i] == '\''))
			to_trim = del[i];
		else if (to_trim != '\0' && del[i] == to_trim)
			to_trim = '\0';
		else
			del[j++] = del[i];
		++i;
	}
	del[j] = '\0';
}
