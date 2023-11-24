/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:41 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:54:42 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "directory_path.h"
#include "utils.h"
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

bool	ft_absolute_path_is_valid(const char *curpath, const char *initial_arg);
bool	ft_isadir(const char *path);
bool	ft_begin_with_dots(char *curpath);

bool	ft_absolute_path_is_valid(const char *curpath, const char *initial_arg)
{
	struct stat	curpath_stat;

	if (stat(curpath, &curpath_stat) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(initial_arg);
		return (false);
	}
	return (true);
}

bool	ft_isadir(const char *path)
{
	struct stat	path_stat;

	return (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode) == true);
}

bool	ft_begin_with_dots(char *curpath)
{
	return (ft_strnstr(curpath, ".\0", 2) != NULL \
			|| ft_strnstr(curpath, "./", 2) != NULL \
			|| ft_strnstr(curpath, "..\0", 3) != NULL \
			|| ft_strnstr(curpath, "../", 3) != NULL);
}
