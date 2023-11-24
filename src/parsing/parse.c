/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:10 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:56:11 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdio.h>

t_parse	ft_parse(t_msh *msh, t_pl *pipeline, char *line);
t_parse	ft_lex_line(t_msh *msh, t_token_container *token_container);
t_parse	ft_q_and_expd(t_msh *msh, t_token_container *token_container);
t_parse	ft_tree(t_msh *msh, t_pl *pipeline, t_token_container *token_container);

t_parse	ft_parse(t_msh *msh, t_pl *pipeline, char *line)
{
	t_token_container	*token_container;
	t_parse				e_parse_ret;

	token_container = ft_lexer_monitor(line);
	e_parse_ret = ft_lex_line(msh, token_container);
	if (e_parse_ret == PARSE_ERROR)
		return (PARSE_ERROR);
	else if (e_parse_ret == NOTHING_TO_PARSE)
		return (NOTHING_TO_PARSE);
	e_parse_ret = ft_q_and_expd(msh, token_container);
	if (e_parse_ret == PARSE_ERROR)
		return (PARSE_ERROR);
	else if (e_parse_ret == NOTHING_TO_PARSE)
		return (NOTHING_TO_PARSE);
	return (ft_tree(msh, pipeline, token_container));
}

t_parse	ft_lex_line(t_msh *msh, t_token_container *token_container)
{
	if (token_container == NULL)
	{
		msh->exit_status = 1;
		ft_putendl_fd("minishell: parse error", 2);
		return (PARSE_ERROR);
	}
	if (token_container->list_size == 0)
	{
		ft_delete_list(token_container);
		return (NOTHING_TO_PARSE);
	}
	return (PARSE_SUCCESS);
}

t_parse	ft_q_and_expd(t_msh *msh, t_token_container *token_container)
{
	if (ft_check_expansion(msh, token_container) == 1)
	{
		msh->exit_status = 1;
		ft_delete_list(token_container);
		return (PARSE_ERROR);
	}
	ft_quoting(token_container);
	if (token_container->list_size == 0)
	{
		ft_delete_list(token_container);
		return (NOTHING_TO_PARSE);
	}
	return (PARSE_SUCCESS);
}

t_parse	ft_tree(t_msh *msh, t_pl *pipeline, t_token_container *token_container)
{
	uint8_t	exit_status;

	exit_status = ft_check_grammar(token_container);
	if (exit_status > 0)
	{
		msh->exit_status = exit_status;
		ft_delete_list(token_container);
		return (PARSE_ERROR);
	}
	exit_status = ft_build_tree(pipeline, token_container);
	if (exit_status > 0)
	{
		msh->exit_status = exit_status;
		ft_delete_list(token_container);
		return (PARSE_ERROR);
	}
	ft_delete_list(token_container);
	return (PARSE_SUCCESS);
}
