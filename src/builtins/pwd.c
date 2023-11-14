#include "builtin.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int			ft_pwd(t_msh *msh, t_pl *pl, char **args);
static int	ft_pwd_fallback(void);

int	ft_pwd(t_msh *msh, t_pl *pl, char **args)
{
	(void)pl;
	(void)args;
	if (msh->cwd == NULL)
		return (ft_pwd_fallback());
	else
		printf("%s\n", msh->cwd);
	return (0);
}

static int	ft_pwd_fallback(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		// perror("pwd");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
