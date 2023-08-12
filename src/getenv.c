/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:23:28 by shinfray          #+#    #+#             */
/*   Updated: 2023/08/12 12:44:11 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_getenv(const char *name, char **env);
static int		ft_strcmp(const char *s1, const char *s2);
static size_t	ft_strlen(const char *s);

char	*ft_getenv(const char *name, char **env)
{
	while (env != NULL && ft_strcmp(*env, name) != 0)
		++env;
	return ((*env) + ft_strlen(name) + 1);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' )
		++i;
	return (i);
}