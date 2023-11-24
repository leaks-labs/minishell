/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:52 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:55:53 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include "init.h"

uint8_t			ft_build_tree(t_pl *pipeline, \
t_token_container *token_container);
static uint8_t	ft_fill_pipeline(t_pl *pipeline, \
t_token_container *token_container);
static uint8_t	ft_fill_agrs(t_pl *pipeline, t_token_list *token_node, \
t_get *get);

uint8_t	ft_build_tree(t_pl *pipeline, t_token_container *token_container)
{
	pipeline->n_cmd = ft_pipeline_len(token_container) + 1;
	pipeline->cmd_list = ft_calloc(pipeline->n_cmd, sizeof(t_cmd));
	if (pipeline->cmd_list == NULL)
		return (1);
	if (ft_alloc_pipeline(pipeline, token_container) == 1 \
		|| ft_fill_pipeline(pipeline, token_container) == 1)
	{
		ft_free_cmd_list(pipeline);
		return (1);
	}
	return (0);
}

static uint8_t	ft_fill_pipeline(t_pl *pipeline, \
t_token_container *token_container)
{
	t_token_list	*token_node;
	t_get			s_get;

	s_get.i = 0;
	token_node = token_container->sentinel_node->next;
	while (s_get.i < pipeline->n_cmd)
	{
		s_get.j = 0;
		s_get.k = 0;
		while (token_node->node_type != SENTINEL_NODE \
				&& token_node->struct_token->operator_type != PIPE)
		{
			if (ft_fill_agrs(pipeline, token_node, &s_get) == 1)
				return (1);
			token_node = token_node->next;
			if (token_node->prev->node_type != SENTINEL_NODE \
				&& ft_is_redir(token_node->prev->struct_token->operator_type))
				token_node = token_node->next;
		}
		token_node = token_node->next;
		++s_get.i;
	}
	return (0);
}

static uint8_t	ft_fill_agrs(t_pl *pipeline, t_token_list *token_node, \
t_get *get)
{
	if (ft_is_redir(token_node->struct_token->operator_type) == true)
	{
		pipeline->cmd_list[get->i].redirect_arr[get->j].file \
			= ft_strdup(token_node->next->struct_token->token);
		if (pipeline->cmd_list[get->i].redirect_arr[get->j].file == NULL)
			return (1);
		pipeline->cmd_list[get->i].redirect_arr[get->j].e_iotype \
			= ft_enum_swap(token_node->struct_token->operator_type);
		++get->j;
	}
	else
	{
		pipeline->cmd_list[get->i].args[get->k] \
			= ft_strdup(token_node->struct_token->token);
		if (pipeline->cmd_list[get->i].args[get->k] == NULL)
			return (1);
		++get->k;
	}
	return (0);
}
