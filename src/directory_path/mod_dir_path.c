/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_dir_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:45 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:54:46 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "directory_path.h"
#include "utils.h"
#include <stdlib.h>

char		*ft_cat_pwd_and_curpath(char *pwd, char *curpath);
void		ft_canonicalize(char *path);
static void	ft_resolve_dotdot(char *path);

char	*ft_cat_pwd_and_curpath(char *pwd, char *curpath)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(pwd);
	tmp = curpath;
	if (len > 0 && pwd[len - 1] == '/')
		curpath = ft_join(2, pwd, curpath);
	else if (len > 0 && pwd[len - 1] != '/')
		curpath = ft_join(3, pwd, "/", curpath);
	free(tmp);
	return (curpath);
}

void	ft_canonicalize(char *path)
{
	const size_t	path_len = ft_strlen(path);
	size_t			i;
	size_t			j;

	i = (path[0] == '/' && path[1] == '/' && path[2] != '/');
	j = i;
	while (i < path_len)
	{
		while (i < path_len && ft_strncmp(path + i, "//", 2) == 0)
			++i;
		if (ft_strncmp(path + i, "/./", 3) == 0 \
			|| ft_strncmp(path + i, "/.\0", 3) == 0)
		{
			i += 2;
			j += (path[i] == '\0');
		}
		else
			path[j++] = path[i++];
	}
	path[j] = '\0';
	if (j > 2 && path[j - 1] == '/')
		path[j - 1] = '\0';
	ft_resolve_dotdot(path);
}

static void	ft_resolve_dotdot(char *path)
{
	const size_t	path_len = ft_strlen(path);
	size_t			i;
	size_t			j;

	i = (path[0] == '/' && path[1] == '/' && path[2] != '/');
	j = i;
	while (i < path_len)
	{
		if (ft_strncmp(path + i, "/../", 4) == 0 \
			|| ft_strncmp(path + i, "/..\0", 4) == 0)
		{
			i += 3;
			j -= (j > 1);
			while (path[j] != '/')
				--j;
			j += (path[i] == '\0');
		}
		else
			path[j++] = path[i++];
	}
	path[j] = '\0';
	if (j > 2 && path[j - 1] == '/')
		path[j - 1] = '\0';
}
