#include "utils.h"

char			*ft_getenv(const char *name, char **env);

char	*ft_getenv(const char *name, char **env)
{
	while (env != NULL && *env != NULL \
			&& (ft_strncmp(*env, name, ft_strlen(name)) != 0 \
			|| (*env)[ft_strlen(name)] != '='))
		++env;
	if (env == NULL || *env == NULL)
		return (NULL);
	return (*env + ft_strlen(name) + 1);
}
