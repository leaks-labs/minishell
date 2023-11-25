/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:49 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 23:17:51 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"
#include <stdlib.h>

int				ft_add_var(t_list *env, const char *arg, int flags);
static t_var	*ft_create_var(const char *str, int flags);

int	ft_add_var(t_list *env, const char *arg, int flags)
{
	t_list_node	*node;
	t_var		*new_var;

	new_var = ft_create_var(arg, flags);
	if (new_var == NULL)
		return (-1);
	node = ft_lstnew(new_var);
	if (node == NULL)
	{
		ft_free_content(new_var);
		return (-1);
	}
	ft_update_env_index(env, new_var, ADD);
	if (env->last_node == NULL)
		ft_lstadd_back(&env->list_node, node);
	else
		ft_lstadd_back(&env->last_node, node);
	env->last_node = node;
	env->n_exported += ((flags & ENV_EXP) == ENV_EXP);
	++env->n_var;
	return (0);
}

static t_var	*ft_create_var(const char *str, int flags)
{
	t_var		*new_var;
	size_t		name_len;

	new_var = ft_calloc(1, sizeof(t_var));
	if (new_var == NULL)
		return (NULL);
	name_len = ft_get_name_len(str);
	new_var->name = ft_strndup(str, name_len);
	if ((flags & ENV_APPEND) == ENV_APPEND)
		new_var->value = ft_strdup(str + name_len + 2);
	else if ((flags & ENV_ASSIGN) == ENV_ASSIGN)
		new_var->value = ft_strdup(str + name_len + 1);
	if (new_var->name == NULL \
		|| (((flags & ENV_ASSIGN) == ENV_ASSIGN \
		|| (flags & ENV_APPEND) == ENV_APPEND) \
		&& new_var->value == NULL))
		return (ft_freef("%p%p%p", new_var->name, new_var->value, new_var));
	if ((flags & ENV_EXP) == ENV_EXP)
		new_var->exported = true;
	return (new_var);
}
