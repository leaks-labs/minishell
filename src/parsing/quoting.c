/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:12 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:56:13 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"

void		ft_quoting(t_token_container *token_container);
static bool	ft_is_removable(t_token_list *token_node);

void	ft_quoting(t_token_container *token_container)
{
	t_token_list	*token_node;
	t_token_list	*tmp_node;

	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
		if (token_node->struct_token->operator_type == NO_OPERATOR \
			&& *token_node->struct_token->token == '\0')
		{
			tmp_node = token_node->next;
			ft_delete_node(token_container, token_node);
			token_node = tmp_node;
		}
		else if (ft_is_removable(token_node) == true)
		{
			ft_rm_quotes(token_node->struct_token->token);
			token_node = token_node->next;
		}
		else
			token_node = token_node->next;
	}
}

static bool	ft_is_removable(t_token_list *token_node)
{
	return (token_node->node_type != SENTINEL_NODE \
			&& token_node->struct_token->operator_type == NO_OPERATOR \
			&& (token_node->prev->node_type == SENTINEL_NODE \
			|| token_node->prev->struct_token->operator_type != HERE_DOC) \
			&& (ft_strchr(token_node->struct_token->token, '"') \
			|| ft_strchr(token_node->struct_token->token, '\'')));
}
