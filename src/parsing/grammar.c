/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:01 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:56:02 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"

uint8_t			ft_check_grammar(t_token_container *token_container);
static uint8_t	ft_monitor_grammar(t_token_list *token_node);
static uint8_t	ft_pipe_rule(t_token_list *token);
static void		ft_empty_redir(void);
static void		ft_unexpected_redir(char *token);

uint8_t	ft_check_grammar(t_token_container *token_container)
{
	t_token_list	*token_node;

	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
		if (token_node->struct_token->operator_type != NO_OPERATOR)
		{
			if (ft_monitor_grammar(token_node) == 2)
				return (2);
		}
		token_node = token_node->next;
	}
	return (0);
}

static uint8_t	ft_monitor_grammar(t_token_list *token_node)
{
	if (token_node->struct_token->operator_type == PIPE)
	{
		if (ft_pipe_rule(token_node) == 2)
			return (2);
	}
	else if (token_node->next->node_type == SENTINEL_NODE)
	{
		ft_empty_redir();
		return (2);
	}
	else if (token_node->next->struct_token->operator_type != NO_OPERATOR)
	{
		ft_unexpected_redir(token_node->next->struct_token->token);
		return (2);
	}
	return (0);
}

static uint8_t	ft_pipe_rule(t_token_list *token_node)
{
	if (token_node->prev->node_type == SENTINEL_NODE \
		|| token_node->prev->struct_token->operator_type != NO_OPERATOR \
		|| token_node->next->node_type == SENTINEL_NODE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token_node->struct_token->token, 2);
		ft_putendl_fd("'", 2);
		return (2);
	}
	return (0);
}

static void	ft_empty_redir(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
}

static void	ft_unexpected_redir(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}
