/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:58 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:54:59 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"

void		ft_remove_var(t_list *env, const char *name);
void		ft_free_content(void *content);
static void	ft_rewire(t_list *env, t_list_node *prev_node, t_list_node *node);

void	ft_remove_var(t_list *env, const char *name)
{
	t_list_node	*node;
	t_list_node	*prev_node;
	t_var		*var;

	node = env->list_node;
	prev_node = NULL;
	while (node != NULL && ft_strcmp(((t_var *)node->content)->name, name) != 0)
	{
		prev_node = node;
		node = node->next;
	}
	if (node != NULL)
	{
		var = (t_var *)node->content;
		ft_rewire(env, prev_node, node);
		ft_update_env_index(env, var, REMOVE);
		ft_lstdelone(node, &ft_free_content);
	}
}

void	ft_free_content(void *content)
{
	t_var	*var;

	if (content == NULL)
		return ;
	var = (t_var *)content;
	ft_freef("%p%p%p", var->name, var->value, var);
}

static void	ft_rewire(t_list *env, t_list_node *prev_node, t_list_node *node)
{
	t_var	*var;

	var = (t_var *)node->content;
	if (prev_node == NULL)
		env->list_node = node->next;
	else
		prev_node->next = node->next;
	if (env->last_node == node)
		env->last_node = prev_node;
	if (var->exported == true)
		--env->n_exported;
	--env->n_var;
}
