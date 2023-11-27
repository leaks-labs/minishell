/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:55 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/25 15:49:24 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdlib.h>

uint8_t	ft_check_expansion(t_msh *msh, t_token_container *token_container);
uint8_t	ft_get_expansion_var(t_list_node **expansion_list, t_index *index, \
char *src);
uint8_t	ft_tokenise_expansion(t_list_node **node, t_index *index, char *src);
void	ft_get_flag(char *src, char *flag);
char	*ft_expand(t_msh *msh, char *src);

uint8_t	ft_check_expansion(t_msh *msh, t_token_container *token_container)
{
	t_token_list	*token_node;
	char			*dst;

	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
		if (token_node->struct_token->operator_type == NO_OPERATOR \
			&& (token_node->prev->struct_token == NULL \
			|| token_node->prev->struct_token->operator_type != HERE_DOC) \
			&& ft_strchr(token_node->struct_token->token, '$'))
		{
			dst = ft_expansion_monitor(msh, token_node->struct_token->token, \
			true);
			if (dst == NULL)
				return (1);
			free(token_node->struct_token->token);
			token_node->struct_token->token = dst;
		}
		token_node = token_node->next;
	}
	return (0);
}

uint8_t	ft_get_expansion_var(t_list_node **expansion_list, t_index *index, \
char *src)
{
	index->current++;
	if (src[index->current] == '?')
	{
		index->current++;
		if (ft_tokenise_expansion(expansion_list, index, src) == 1)
			return (1);
	}
	else
	{
		while ((src[index->current] == '_' || ft_isalnum(src[index->current])))
			index->current++;
		if (ft_tokenise_expansion(expansion_list, index, src) == 1)
			return (1);
	}
	index->previous = index->current;
	return (0);
}

uint8_t	ft_tokenise_expansion(t_list_node **node, t_index *index, char *src)
{
	t_list_node	*new_node;
	char		*str;

	str = ft_substr(src, (unsigned int)index->previous, \
		index->current - index->previous);
	if (str == NULL)
		return (1);
	new_node = ft_lstnew(str);
	if (new_node == NULL)
	{
		free(str);
		return (1);
	}
	ft_lstadd_back(node, new_node);
	return (0);
}

void	ft_get_flag(char *src, char *flag)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		if (*flag == '\0' && (ft_strchr("'\"", src[i]) != NULL))
			*flag = src[i];
		else if (*flag != '\0' && src[i] == *flag)
			*flag = '\0';
		++i;
	}
}

char	*ft_expand(t_msh *msh, char *src)
{
	char	*dst;
	char	buf[4];

	if (src[1] == '?')
	{
		ft_uimaxtostr(buf, 4, msh->exit_status);
		dst = ft_strdup(buf);
	}
	else
	{
		dst = ft_getenv(&src[1], &msh->env);
		if (dst != NULL)
			dst = ft_strdup(dst);
		else
			dst = ft_strdup("");
	}
	return (dst);
}
