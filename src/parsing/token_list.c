/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:17 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:56:18 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>

t_token_container	*ft_create_list(void);
void				ft_delete_list(t_token_container *token_container);
void				ft_delete_node(t_token_container *token_container, \
t_token_list *node_to_del);
t_token				*ft_tokenise(t_lexer_operator operator_type, char *line, \
t_index *index);
t_token_list		*ft_append(t_token_container *token_container, \
t_token *struct_token);

t_token_container	*ft_create_list(void)
{
	t_token_container	*token_container;
	t_token_list		*token_sentinel;

	token_container = ft_calloc(1, sizeof(t_token_container));
	if (token_container == NULL)
		return (NULL);
	token_sentinel = ft_calloc(1, sizeof(t_token_list));
	if (token_sentinel == NULL)
		return (ft_freef("%p", token_container));
	token_container->sentinel_node = token_sentinel;
	token_container->list_size = 0;
	token_sentinel->next = token_sentinel;
	token_sentinel->prev = token_sentinel;
	token_sentinel->node_type = SENTINEL_NODE;
	token_sentinel->struct_token = NULL;
	return (token_container);
}

void	ft_delete_list(t_token_container	*token_container)
{
	t_token_list	*token_node;
	t_token_list	*token_tmp;

	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
		token_tmp = token_node;
		token_node = token_node->next;
		ft_freef("%p, %p, %p", token_tmp->struct_token->token, \
		token_tmp->struct_token, token_tmp);
	}
	ft_freef("%p, %p", token_node, token_container);
}

void	ft_delete_node(t_token_container *token_container, \
t_token_list *node_to_del)
{
	if (node_to_del == token_container->sentinel_node)
		return ;
	node_to_del->next->prev = node_to_del->prev;
	node_to_del->prev->next = node_to_del->next;
	ft_freef("%p, %p, %p", node_to_del->struct_token->token, \
	node_to_del->struct_token, node_to_del);
	token_container->list_size--;
}

t_token	*ft_tokenise(t_lexer_operator operator_type, char *line, t_index *index)
{
	t_token	*struct_token;

	struct_token = ft_calloc(1, sizeof(t_token));
	if (struct_token == NULL)
		return (NULL);
	struct_token->operator_type = operator_type;
	struct_token->token = ft_substr(line, (unsigned int)index->previous, \
	index->current - index->previous);
	if (struct_token->token == NULL)
	{
		free(struct_token);
		struct_token = NULL;
	}
	return (struct_token);
}

t_token_list	*ft_append(t_token_container *token_container, \
t_token *struct_token)
{
	t_token_list	*token_sentinel;
	t_token_list	*prev_token;
	t_token_list	*new_token;

	token_sentinel = token_container->sentinel_node;
	prev_token = token_sentinel->prev;
	new_token = ft_calloc(1, sizeof(t_token_list));
	if (new_token == NULL)
		return (NULL);
	new_token->next = token_sentinel;
	new_token->prev = prev_token;
	new_token->node_type = NODE;
	new_token->struct_token = struct_token;
	token_sentinel->prev = new_token;
	prev_token->next = new_token;
	token_container->list_size++;
	return (new_token);
}
