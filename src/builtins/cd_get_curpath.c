/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_curpath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:08 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:54:09 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "directory_path.h"
#include "env.h"
#include "exec.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

char		*ft_get_curpath(const char **args, t_msh *msh, bool *print_m);
static char	*ft_init_curpath(const char **args, t_msh *msh, bool *print_m);
static char	*ft_retrieve_from_env(t_list *env, const char *arg, bool *print_m);
static char	*ft_iterate_cdpath(t_list *env, char *curpath);
static char	*ft_form_cdpath(char *cdpath, char *curpath);

char	*ft_get_curpath(const char **args, t_msh *msh, bool *print_m)
{
	char	*curpath;

	curpath = ft_init_curpath(args, msh, print_m);
	if (curpath == NULL)
		return (NULL);
	if (*curpath != '/')
		curpath = ft_iterate_cdpath(&msh->env, curpath);
	if (*curpath != '/')
	{
		curpath = ft_cat_pwd_and_curpath(msh->cwd, curpath);
		if (curpath == NULL)
			return (NULL);
	}
	if (ft_absolute_path_is_valid(curpath, *args) == false)
		return (ft_freef("%p", curpath));
	ft_canonicalize(curpath);
	return (curpath);
}

static char	*ft_init_curpath(const char **args, t_msh *msh, bool *print_m)
{
	char	*curpath;

	curpath = NULL;
	if (args[0] != NULL && args[1] != NULL)
		ft_putendl_fd("bash: cd: too many arguments\n", STDERR_FILENO);
	else if (*args == NULL || ft_strcmp(*args, "-") == 0)
		curpath = ft_retrieve_from_env(&msh->env, *args, print_m);
	else
		curpath = ft_strdup(*args);
	return (curpath);
}

static char	*ft_retrieve_from_env(t_list *env, const char *arg, bool *print_m)
{
	t_var	*var;
	char	*curpath;

	var = NULL;
	curpath = NULL;
	if (arg == NULL)
	{
		var = ft_get_var(env, "HOME");
		if (var == NULL || var->value == NULL)
			ft_putendl_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		var = ft_get_var(env, "OLDPWD");
		if (var == NULL || var->value == NULL)
			ft_putendl_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		else
			*print_m = true;
	}
	if (var != NULL)
		curpath = ft_strdup(var->value);
	return (curpath);
}

static char	*ft_iterate_cdpath(t_list *env, char *curpath)
{
	char	**cdpath;
	char	*tmp;
	size_t	i;

	if (ft_begin_with_dots(curpath) == false)
	{
		cdpath = ft_split(ft_getenv("CDPATH", env), ':');
		if (cdpath == NULL)
			return (curpath);
		i = 0;
		while (cdpath[i] != NULL)
		{
			tmp = ft_form_cdpath(cdpath[i++], curpath);
			if (tmp != NULL && ft_isadir(tmp) == true)
			{
				free(curpath);
				curpath = tmp;
				break ;
			}
			free(tmp);
		}
		ft_freef("%P", cdpath);
	}
	return (curpath);
}

static char	*ft_form_cdpath(char *cdpath, char *curpath)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(cdpath);
	if (len > 0 && cdpath[len - 1] == '/')
		tmp = ft_join(2, cdpath, curpath);
	else if (len > 0 && cdpath[len - 1] != '/')
		tmp = ft_join(3, cdpath, "/", curpath);
	else
		tmp = ft_join(2, "./", curpath);
	return (tmp);
}
