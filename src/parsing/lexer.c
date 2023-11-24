/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:07 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:56:08 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>

t_token_container	*ft_lexer_monitor(char *line);
static t_lexer		ft_lexer_read(t_token_container *token_container, \
char *line);
t_dictionary		ft_search_operator(char *line);
static t_lexer		ft_line_lexer(t_token_container *token_container, \
char *line, t_dictionary *dictionary, t_index *index);

t_token_container	*ft_lexer_monitor(char *line)
{
	t_token_container	*token_container;

	token_container = ft_create_list();
	if (token_container == NULL)
		return (NULL);
	if (ft_lexer_read(token_container, line) == NOT_LEXED)
	{
		ft_delete_list(token_container);
		token_container = NULL;
	}
	return (token_container);
}

static t_lexer	ft_lexer_read(t_token_container *token_container, char *line)
{
	t_token			*token;
	t_index			s_index;
	t_dictionary	s_dictionary;

	token = NULL;
	s_index.current = 0;
	s_index.previous = s_index.current;
	while (line[s_index.current] != '\0')
	{
		s_dictionary = ft_search_operator(&line[s_index.current]);
		if (ft_line_lexer(token_container, line, \
			&s_dictionary, &s_index) == NOT_LEXED)
			return (NOT_LEXED);
	}
	if (s_index.previous != s_index.current)
	{
		token = ft_tokenise(s_dictionary.operator_type, line, &s_index);
		if (token == NULL || ft_append(token_container, token) == NULL)
		{
			free(token);
			return (NOT_LEXED);
		}
	}
	return (LEXED);
}

t_dictionary	ft_search_operator(char *line)
{
	const t_dictionary	s_dictionary[DICTIONARY_SIZE] = {
	{HERE_DOC, 2, "<<"}, {APPEND, 2, ">>"},
	{INPUT, 1, "<"}, {OUTPUT, 1, ">"},
	{PIPE, 1, "|"}, {NO_OPERATOR, 0, {0}}};
	size_t				i;

	i = 0;
	while (i < DICTIONARY_SIZE - 1)
	{
		if (ft_strncmp(line, s_dictionary[i].operator,
				s_dictionary[i].len) == OPERATOR)
			return (s_dictionary[i]);
		i++;
	}
	return (s_dictionary[NO_OPERATOR]);
}

static t_lexer	ft_line_lexer(t_token_container *token_container, char *line, \
t_dictionary	*dictionary, t_index *index)
{
	if (((dictionary->operator_type != NO_OPERATOR \
		|| ft_isspace(line[index->current]) == true) \
		&& index->previous != index->current) \
		&& ft_get_token(token_container, line, NO_OPERATOR, index) \
		== NOT_LEXED)
	{
		return (NOT_LEXED);
	}
	if (dictionary->operator_type != NO_OPERATOR)
	{
		index->current += dictionary->len;
		if (ft_get_token(token_container, line, dictionary->operator_type, \
				index) == NOT_LEXED)
			return (NOT_LEXED);
	}
	else if (line[index->current] == '"' || line[index->current] == '\'')
	{
		if (ft_skip_quotes(line, index) == NOT_LEXED)
			return (NOT_LEXED);
	}
	else
		ft_get_next_index(line, index);
	return (LEXED);
}
