/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:59 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 16:27:29 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdlib.h>

#include <stdio.h>

char			*ft_expansion_monitor(t_msh *msh, char *src, bool handle_quote);
static uint8_t	ft_get_expansion_list(t_list_node **expansion_list, char *src);
static char		*ft_command_expand(t_msh *msh, t_list_node *expansion_list, \
bool handle_quote);
static bool		ft_is_expandable(char *str, bool handle_quote, char flag);

char	*ft_expansion_monitor(t_msh *msh, char *src, bool handle_quote)
{
	t_list_node	*expansion_list;
	char		*dst;

	expansion_list = NULL;
	if (ft_get_expansion_list(&expansion_list, src) == 1)
	{
		ft_lstclear(&expansion_list, NULL);
		return (NULL);
	}
	dst = ft_command_expand(msh, expansion_list, handle_quote);
	ft_lstclear(&expansion_list, NULL);
	return (dst);
}

static uint8_t	ft_get_expansion_list(t_list_node **expansion_list, char *src)
{
	t_index	s_index;

	s_index.current = 0;
	s_index.previous = s_index.current;
	while (src[s_index.current] != '\0')
	{
		if (src[s_index.current] == '$' && s_index.current != s_index.previous)
		{
			if (ft_tokenise_expansion(expansion_list, &s_index, src) == 1)
				return (1);
			s_index.previous = s_index.current;
		}
		if ((src[s_index.current] == '$' && (src[s_index.current + 1] == '_' \
					|| src[s_index.current + 1] == '?' \
					|| ft_isalpha(src[s_index.current + 1]))) \
			&& ft_get_expansion_var(expansion_list, &s_index, src) == 1)
			return (1);
		else if (src[s_index.current] != '\0' && src[s_index.current] != '$')
			s_index.current++;
	}
	if (s_index.previous != s_index.current \
		&& ft_tokenise_expansion(expansion_list, &s_index, src) == 1)
		return (1);
	return (0);
}

char	*ft_command_expand(t_msh *msh, t_list_node *expansion_list, \
bool handle_quote)
{
	t_join	s_join;
	char	flag;

	flag = '\0';
	s_join.dst = ft_strdup("");
	while (s_join.dst != NULL && expansion_list != NULL)
	{
		s_join.src = (char *)expansion_list->content;
		ft_get_flag(s_join.src, &flag);
		if (ft_is_expandable(s_join.src, handle_quote, flag) == true)
		{
			s_join.src = ft_expand(msh, s_join.src);
			if (s_join.src == NULL)
				return (ft_freef("%p", s_join.dst));
		}
		s_join.tmp = s_join.dst;
		s_join.dst = ft_join(2, s_join.dst, s_join.src);
		ft_freef("%p", s_join.tmp);
		if (s_join.src != expansion_list->content)
			free(s_join.src);
		expansion_list = expansion_list->next;
	}
	return (s_join.dst);
}

static bool	ft_is_expandable(char *str, bool handle_quote, char flag)
{
	return ((handle_quote == false || flag != '\'') \
		&& (str[0] == '$' \
		&& (str[1] == '_' || str[1] == '?' || ft_isalpha(str[1]))));
}
