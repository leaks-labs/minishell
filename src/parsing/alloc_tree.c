/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:47 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:59:39 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"

uint8_t			ft_alloc_pipeline(t_pl *pipeline, \
t_token_container *token_container);
static void		ft_reset_args(t_pl_args *pl_args);
static void		ft_set_args(t_token_list *token_node, t_pl_args *pl_args);
static uint8_t	ft_alloc_args(t_pl *pipeline, t_pl_args *pl_args, size_t i);

uint8_t	ft_alloc_pipeline(t_pl *pipeline, t_token_container *token_container)
{
	t_token_list	*token_node;
	t_pl_args		s_pl_args;
	size_t			i;

	token_node = token_container->sentinel_node->next;
	i = 0;
	while (i < pipeline->n_cmd)
	{
		ft_reset_args(&s_pl_args);
		while (token_node->node_type != SENTINEL_NODE \
				&& token_node->struct_token->operator_type != PIPE)
		{
			ft_set_args(token_node, &s_pl_args);
			token_node = token_node->next;
			if (token_node->prev->node_type != SENTINEL_NODE \
				&& ft_is_redir(token_node->prev->struct_token->operator_type))
				token_node = token_node->next;
		}
		token_node = token_node->next;
		if (ft_alloc_args(pipeline, &s_pl_args, i) == 1)
			return (1);
		++i;
	}
	return (0);
}

static void	ft_reset_args(t_pl_args *pl_args)
{
	pl_args->n_args = 0;
	pl_args->n_redirect = 0;
}

static void	ft_set_args(t_token_list *token_node, t_pl_args *pl_args)
{
	if (ft_is_redir(token_node->struct_token->operator_type) == true)
		pl_args->n_redirect++;
	else
		pl_args->n_args++;
}

static uint8_t	ft_alloc_args(t_pl *pipeline, t_pl_args *pl_args, size_t i)
{
	if (pl_args->n_args > 0)
	{
		pipeline->cmd_list[i].args
			= ft_calloc(pl_args->n_args + 1, sizeof(char *));
		if (pipeline->cmd_list[i].args == NULL)
			return (1);
	}
	if (pl_args->n_redirect > 0)
	{
		pipeline->cmd_list[i].n_redirect = pl_args->n_redirect;
		pipeline->cmd_list[i].redirect_arr \
			= ft_calloc(pl_args->n_redirect, sizeof(t_redirect));
		if (pipeline->cmd_list[i].redirect_arr == NULL)
			return (1);
	}
	else
	{
		pipeline->cmd_list[i].n_redirect = pl_args->n_redirect;
		pipeline->cmd_list[i].redirect_arr = NULL;
	}
	return (0);
}
