/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:43 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:55:44 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "directory_path.h"
#include "env.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

t_msh		*ft_struct_init(char **envp);
static char	*ft_get_first_cwd(t_list *env);
static bool	ft_issameinode(char *p1, char *p2);
static void	ft_set_shlvl(t_list *env);

t_msh	*ft_struct_init(char **envp)
{
	t_msh	*msh;

	msh = ft_calloc(1, sizeof(t_msh));
	if (msh == NULL)
		return (NULL);
	if (ft_env_to_list(&msh->env, envp) == -1)
		return (ft_freef("%p", msh));
	msh->cwd = ft_get_first_cwd(&msh->env);
	if (msh->cwd == NULL)
	{
		ft_lstclear(&msh->env.list_node, &ft_free_content);
		return (ft_freef("%p", msh));
	}
	ft_set_shlvl(&msh->env);
	return (msh);
}

static char	*ft_get_first_cwd(t_list *env)
{
	char		*path;
	char		*pwd_from_env;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (NULL);
	pwd_from_env = ft_getenv("PWD", env);
	if (pwd_from_env != NULL)
		pwd_from_env = ft_strdup(pwd_from_env);
	if (pwd_from_env == NULL)
		return (path);
	if (*pwd_from_env != '/' || ft_issameinode(path, pwd_from_env) == false)
	{
		free(pwd_from_env);
		return (path);
	}
	free(path);
	ft_canonicalize(pwd_from_env);
	return (pwd_from_env);
}

static bool	ft_issameinode(char *p1, char *p2)
{
	struct stat	buf_p1;
	struct stat	buf_p2;

	return (stat(p1, &buf_p1) == 0 && stat(p2, &buf_p2) == 0 \
			&& buf_p1.st_ino == buf_p2.st_ino);
}

static void	ft_set_shlvl(t_list *env)
{
	t_var		*shlvl;
	int32_t		lvl;
	bool		error;
	char		new_lvl[MAX_SHLVL_NUM_LEN + 1];

	shlvl = ft_get_var(env, "SHLVL");
	lvl = 1;
	error = false;
	if (shlvl != NULL && shlvl->value != NULL)
	{
		lvl = (int32_t)(ft_strtoimax(shlvl->value, &error) + 1);
		if (error == true)
			lvl = 1;
		else if (lvl > MAX_SHLVL)
		{
			printf("minishell: warning: shell level (%d) too high, ", lvl);
			printf("resetting to 1\n");
			lvl = 1;
		}
		else if (lvl < 0)
			lvl = 0;
	}
	ft_uimaxtostr(new_lvl, MAX_SHLVL_NUM_LEN + 1, (uintmax_t)lvl);
	ft_mod_env2(env, "SHLVL", new_lvl, ENV_EXP);
}
