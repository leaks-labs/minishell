#include "builtin.h"
#include "env.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int			ft_cd(t_msh *msh, t_pl *pl, char **args);
static void	ft_update_pwd_vars(t_list *env, char *curpath);

int	ft_cd(t_msh *msh, t_pl *pl, char **args)
{
	char	*curpath;
	bool	print_m;

	(void)pl;
	print_m = false;
	curpath = ft_get_curpath((const char **)args, msh, &print_m);
	if (curpath == NULL)
		return (1);
	if (chdir(curpath) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(*args);
		free(curpath);
		return (1);
	}
	if (print_m == true)
		printf("%s\n", curpath);
	ft_update_pwd_vars(&msh->env, curpath);
	free(msh->cwd);
	msh->cwd = curpath;
	return (0);
}

static void	ft_update_pwd_vars(t_list *env, char *curpath)
{
	t_var	*pwd;

	pwd = ft_get_var(env, "PWD");
	if (pwd != NULL)
		ft_mod_env2(env, "OLDPWD", pwd->value, 0);
	ft_mod_env2(env, "PWD", curpath, 0);
	// catch errors update_pwd_vars errors?
}
