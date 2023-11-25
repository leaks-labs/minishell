/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_cdpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 02:09:39 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/25 10:38:47 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "exec.h"
#include "path.h"
#include "utils.h"
#include <stdlib.h>

t_list_node			*ft_get_cdpath(t_list *env);
static t_list_node	*ft_split_cdpath(const char *str);
static char			*ft_get_a_cdpath_member(const char *str, size_t token_len);

t_list_node	*ft_get_cdpath(t_list *env)
{
	char	*cdpath_one_line;

	cdpath_one_line = ft_getenv("CDPATH", env);
	if (cdpath_one_line == NULL || cdpath_one_line[0] == '\0')
		return (NULL);
	return (ft_split_cdpath(cdpath_one_line));
}

static t_list_node	*ft_split_cdpath(const char *str)
{
	t_list_node	*cdpath_token_list;
	size_t		n_dir;
	size_t		token_len;
	char		*value;

	cdpath_token_list = NULL;
	n_dir = 1;
	while (*str != '\0' || n_dir > 0)
	{
		token_len = ft_path_token_len(str);
		value = ft_get_a_cdpath_member(str, token_len);
		cdpath_token_list = ft_append_token(cdpath_token_list, value);
		if (cdpath_token_list == NULL)
			break ;
		str += token_len;
		n_dir -= 1 - (*str == ':');
		str += (*str == ':');
	}
	return (cdpath_token_list);
}

static char	*ft_get_a_cdpath_member(const char *str, size_t token_len)
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
		value = ft_strdup("");
	return (value);
}
