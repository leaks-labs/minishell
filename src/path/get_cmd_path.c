/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:29:55 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 22:37:38 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include "utils.h"
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

char		*ft_get_cmd_path(t_list_node *path, const char *cmd);
bool		ft_isapath(const char *str);
static char	*ft_check_one_path(const char *cmd);
static char	*ft_search_in_path(t_list_node *path, const char *cmd);

char	*ft_get_cmd_path(t_list_node *path, const char *cmd)
{
	char	*cmd_path;

	if (*cmd == '\0')
	{
		errno = ENOENT;
		return (NULL);
	}
	if (ft_isapath(cmd) == true)
		cmd_path = ft_check_one_path(cmd);
	else if (path != NULL)
		cmd_path = ft_search_in_path(path, cmd);
	else
		cmd_path = ft_strdup(cmd);
	return (cmd_path);
}

bool	ft_isapath(const char *str)
{
	while (*str != '\0' && *str != '/')
		++str;
	return (*str == '/');
}

static char	*ft_check_one_path(const char *cmd)
{
	char		*cmd_path;
	struct stat	buf;

	cmd_path = NULL;
	if (stat(cmd, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode) == true)
			errno = EISDIR;
		else
			cmd_path = ft_strdup(cmd);
	}
	return (cmd_path);
}

static char	*ft_search_in_path(t_list_node *path, const char *cmd)
{
	char		*cmd_path;
	struct stat	buf;
	t_list_node	*node;

	cmd_path = NULL;
	node = path;
	while (node != NULL)
	{
		cmd_path = ft_join(2, (char *)node->content, cmd);
		if (cmd_path == NULL)
			return (NULL);
		if (stat(cmd_path, &buf) == 0)
		{
			if (S_ISDIR(buf.st_mode) == true)
			{
				cmd_path = ft_freef("%p", cmd_path);
				errno = EISDIR;
			}
			break ;
		}
		cmd_path = ft_freef("%p", cmd_path);
		node = node->next;
	}
	return (cmd_path);
}
