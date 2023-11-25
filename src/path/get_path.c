/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:25 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/25 01:46:54 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include "utils.h"
#include <stdlib.h>

t_list_node			*ft_get_path(t_list *env);
size_t				ft_path_token_len(const char *str);
t_list_node			*ft_append_token(t_list_node *path_token_list, char *value);
static t_list_node	*ft_split_path(const char *str);
static char			*ft_get_one_path_member(const char *str, size_t token_len);

t_list_node	*ft_get_path(t_list *env)
{
	char	*path_one_line;

	path_one_line = ft_getenv("PATH", env);
	if (path_one_line == NULL || path_one_line[0] == '\0')
		return (NULL);
	return (ft_split_path(path_one_line));
}

size_t	ft_path_token_len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != ':')
		++i;
	return (i);
}

t_list_node	*ft_append_token(t_list_node *path_token_list, char *value)
{
	t_list_node	*node;

	if (value == NULL)
	{
		ft_lstclear(&path_token_list, NULL);
		return (NULL);
	}
	node = ft_lstnew(value);
	if (node == NULL)
	{
		free(value);
		ft_lstclear(&path_token_list, NULL);
		return (NULL);
	}
	ft_lstadd_back(&path_token_list, node);
	return (path_token_list);
}

static t_list_node	*ft_split_path(const char *str)
{
	t_list_node	*path_token_list;
	size_t		n_dir;
	size_t		token_len;
	char		*value;

	path_token_list = NULL;
	n_dir = 1;
	while (*str != '\0' || n_dir > 0)
	{
		token_len = ft_path_token_len(str);
		value = ft_get_one_path_member(str, token_len);
		path_token_list = ft_append_token(path_token_list, value);
		if (path_token_list == NULL)
			break ;
		str += token_len;
		n_dir -= 1 - (*str == ':');
		str += (*str == ':');
	}
	return (path_token_list);
}

static char	*ft_get_one_path_member(const char *str, size_t token_len)
{
	char	*value;
	char	*tmp;

	if (token_len > 0)
	{
		value = ft_strndup(str, token_len);
		if (value == NULL)
			return (NULL);
		if (value[token_len - 1] != '/')
		{
			tmp = value;
			value = ft_join(2, value, "/");
			free(tmp);
		}
	}
	else
		value = ft_strdup("./");
	return (value);
}
