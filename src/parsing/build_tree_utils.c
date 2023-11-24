/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:49 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:55:50 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t		ft_pipeline_len(t_token_container *token_container);
bool		ft_is_redir(t_lexer_operator e_operator_type);
t_io_type	ft_enum_swap(t_lexer_operator e_lexer_operator);

size_t	ft_pipeline_len(t_token_container *token_container)
{
	t_token_list	*token_node;
	size_t			n_cmd;

	n_cmd = 0;
	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
		if (token_node->struct_token->operator_type != NO_OPERATOR \
			&& token_node->struct_token->operator_type == PIPE)
			++n_cmd;
		token_node = token_node->next;
	}
	return (n_cmd);
}

bool	ft_is_redir(t_lexer_operator e_operator_type)
{
	return (e_operator_type == HERE_DOC || e_operator_type == APPEND \
			|| e_operator_type == INPUT || e_operator_type == OUTPUT);
}

t_io_type	ft_enum_swap(t_lexer_operator e_lexer_operator)
{
	if (e_lexer_operator == HERE_DOC)
		return (IO_HEREDOC);
	else if (e_lexer_operator == APPEND)
		return (IO_APPEND);
	else if (e_lexer_operator == INPUT)
		return (IO_INPUT);
	else
		return (IO_OUTPUT);
}
