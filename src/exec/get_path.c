#include "exec.h"
#include "utils.h"
#include <stdlib.h>

char		**ft_get_path(t_list *env);
static char	**ft_set_slash(char **path);

char	**ft_get_path(t_list *env)
{
	char	**path;

	path = ft_split(ft_getenv("PATH", env), ':');
	if (path == NULL)
		return (NULL);
	return (ft_set_slash(path));
}

static char	**ft_set_slash(char **path)
{
	char	*temp;
	int		i;

	i = 0;
	while (path != NULL && path[i] != NULL)
	{
		temp = ft_join(2, path[i], "/");
		if (temp == NULL)
		{
			// perror("ft_strjoin");
			return (ft_freef("%P", path));
		}
		free(path[i]);
		path[i++] = temp;
	}
	return (path);
}
