#include "path.h"
#include "utils.h"
#include <stdlib.h>

char		**ft_get_path(t_list *env);
static char	**ft_set_slash(char **path);

char	**ft_get_path(t_list *env)
{
	char	**path;

	path = ft_split(ft_getenv("PATH", env), ':');
	if (path != NULL)
		path = ft_set_slash(path);
	return (path);
}

static char	**ft_set_slash(char **path)
{
	char	*temp;
	size_t	len;
	size_t	i;

	i = 0;
	while (path != NULL && path[i] != NULL)
	{
		len = ft_strlen(path[i]);
		if (len > 0 && path[i][len - 1] != '/')
		{
			temp = ft_join(2, path[i], "/");
			if (temp == NULL)
				return (ft_freef("%P", path));
			free(path[i]);
			path[i] = temp;
		}
		++i;
	}
	return (path);
}
