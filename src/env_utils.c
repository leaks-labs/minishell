/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:23:28 by shinfray          #+#    #+#             */
/*   Updated: 2023/08/12 16:40:53y shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**ft_envcpy(char **envp);
char			*ft_getenv(const char *name, char **env);
static size_t	ft_dptrlen(char	**dptr);
static char		**ft_free_dptr(char **dptr);

char	**ft_envcpy(char **envp)
{
	char	**envp_cpy;
	size_t	i;

	//decide if we return NULL or a char ** malloc with an empty string in
	//the case where envp or *envp == NULL (and is it possible to have
	// envp or *envp == NULL?)
	if (envp == NULL)
		return (NULL);

	envp_cpy = ft_calloc(ft_dptrlen(envp) + 1, sizeof(*envp_cpy));
	if (envp_cpy == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		envp_cpy[i] = ft_strdup(envp[i]);
		if (envp_cpy[i] == NULL)
			return (ft_free_dptr(envp_cpy));
		++i;
	}
	return (envp_cpy);
}

char	*ft_getenv(const char *name, char **env)
{
	while (env != NULL && *env != NULL \
			&& (ft_strncmp(*env, name, ft_strlen(name)) != 0 \
			|| *env[ft_strlen(name)] != '='))
		++env;
	if (env == NULL || *env == NULL)
		return (NULL);
	return (*env + ft_strlen(name) + 1);
}

static size_t	ft_dptrlen(char	**dptr)
{
	size_t	i;

	i = 0;
	while (dptr[i] != NULL)
		++i;
	return (i);
}

static char	**ft_free_dptr(char **dptr)
{
	char	**ptr;

	ptr = dptr;
	while (*dptr != NULL)
		free(*dptr++);
	free(ptr);
	return (NULL);
}
