/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:51 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 23:31:04 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"

bool	ft_isvalidname(const char *name);
bool	ft_isassignation(const char *str);
bool	ft_isappend(const char *str);
t_var	*ft_get_var(t_list *env, const char *name);
size_t	ft_get_name_len(const char *var);

bool	ft_isvalidname(const char *name)
{
	if (*name != '_' && ft_isalpha(*name) == false)
		return (false);
	++name;
	while (*name != '\0' && (*name == '_' || ft_isalnum(*name) == true))
		++name;
	return (*name == '\0' || *name == '=' || ft_strncmp(name, "+=", 2) == 0);
}

bool	ft_isassignation(const char *str)
{
	return (ft_strchr(str, '=') != NULL);
}

bool	ft_isappend(const char *str)
{
	char	*tmp;

	tmp = ft_strchr(str, '=');
	return (tmp != NULL && *(tmp - 1) == '+');
}

t_var	*ft_get_var(t_list *env, const char *name)
{
	const size_t	name_l = ft_get_name_len(name);
	t_list_node		*node;
	t_var			*var;

	if (name_l == 0)
		return (NULL);
	node = env->list_node;
	while (node != NULL)
	{
		var = (t_var *)node->content;
		if (ft_strncmp(var->name, name, name_l) == 0 \
			&& var->name[name_l] == '\0')
			return (var);
		node = node->next;
	}
	return (NULL);
}

size_t	ft_get_name_len(const char *var)
{
	const char	*tmp;

	tmp = var;
	while (*tmp != '\0' && *tmp != '=' && *tmp != '+')
		++tmp;
	return ((size_t)(tmp - var));
}
