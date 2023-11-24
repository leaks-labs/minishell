/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:01 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:55:02 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"

void	ft_update_env_index(t_list *env, t_var *var, t_idx_act e_idx_act);
t_var	*ft_get_var_per_index(t_list *env, size_t i);

void	ft_update_env_index(t_list *env, t_var *var, t_idx_act e_idx_act)
{
	t_list_node	*node;
	t_var		*env_var;

	if (env->list_node == NULL)
		return ;
	node = env->list_node;
	while (node != NULL)
	{
		env_var = (t_var *)node->content;
		if (e_idx_act == ADD)
		{
			if (ft_strcmp(env_var->name, var->name) < 0)
				++var->index;
			else
				++env_var->index;
		}
		else if (e_idx_act == REMOVE)
			if (ft_strcmp(env_var->name, var->name) > 0)
				--env_var->index;
		node = node->next;
	}
}

t_var	*ft_get_var_per_index(t_list *env, size_t i)
{
	t_list_node	*node;
	t_var		*var;

	node = env->list_node;
	while (node != NULL)
	{
		var = ((t_var *)node->content);
		if (i != var->index)
			node = node->next;
		else
			return (var);
	}
	return (NULL);
}
