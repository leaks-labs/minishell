#include "lexer.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>

t_token_container	*ft_lexer_monitor(char *line);
static t_lexer 		ft_lexer_read(t_token_container *token_container, char *line);
t_dictionary		ft_serach_operator(char *line); //search
static t_lexer		ft_line_lexer(t_token_container *token_container, char *line, t_dictionary *dictionary, t_index *index);

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

static t_lexer ft_lexer_read(t_token_container *token_container, char *line)
{
	t_token			*token;
    t_index 		index;
    t_dictionary	dictionary;

	token = NULL;
    index.current = 0;
    index.previous = index.current;
    while (line[index.current] != '\0')
    {
        dictionary = ft_serach_operator(&line[index.current]);
        if (ft_line_lexer(token_container, line, &dictionary, &index) == NOT_LEXED)
            return (NOT_LEXED);
    }
	if (index.previous != index.current)
	{
		token = ft_tokenise(dictionary.operator_type, line, &index);
		if (token == NULL || ft_append(token_container, token) == NULL) //free token
			return (NOT_LEXED);
	}
    return (LEXED);
}

t_dictionary ft_serach_operator(char *line)
{
	const t_dictionary	dictionary[DICTIONARY_SIZE] =
	{
	{HERE_DOC, 2, "<<"}, {APPEND, 2, ">>"},
	{INPUT, 1, "<"}, {OUTPUT, 1, ">"},
	{PIPE, 1, "|"}, {NO_OPERATOR, 0, {0}}
	};
    size_t         i;

    i = 0;
    while (i < DICTIONARY_SIZE - 1)
	{
		if (ft_strncmp(line, dictionary[i].operator, dictionary[i].len) == OPERATOR)
			return (dictionary[i]);
		i++;
	}
	return (dictionary[NO_OPERATOR]);
}

static t_lexer	ft_line_lexer(t_token_container *token_container, char *line, t_dictionary	*dictionary, t_index *index)
{
	if ((dictionary->operator_type != NO_OPERATOR || ft_isspace(line[index->current]) == true) && index->previous != index->current)
	{
		if (ft_get_token(token_container, line, NO_OPERATOR, index) == NOT_LEXED)
			return (NOT_LEXED);
	}
	if (dictionary->operator_type != NO_OPERATOR)
	{
		index->current += dictionary->len;
		if (ft_get_token(token_container, line, dictionary->operator_type, index) == NOT_LEXED)
			return (NOT_LEXED);
	}
	else if (line[index->current] == '"' || line[index->current] == '\'') //strchr
	{
		if (ft_skip_quotes(line, index) == NOT_LEXED)
			return (NOT_LEXED);
	}
	else
		ft_get_next_index(line, index);
	return (LEXED);
}