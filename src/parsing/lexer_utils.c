#include "lexer.h"
#include "utils.h"

t_lexer ft_get_token(t_token_container *token_container, char *line, t_lexer_operator operator, t_index *index);
t_lexer ft_skip_quotes(char *line, t_index *index);
void    ft_get_next_index(char *line, t_index *index);

t_lexer ft_get_token(t_token_container *token_container, char *line, t_lexer_operator operator, t_index *index)
{
    t_token *token;

    token = ft_tokenise(operator, line, index);
    if (token == NULL || ft_append(token_container, token) == NULL) //free token
        return (NOT_LEXED);
    while (ft_isspace(line[index->current]) == true)
        index->current++;
    index->previous = index->current;
    return (LEXED);
}

t_lexer ft_skip_quotes(char *line, t_index *index)
{
    const char tmp = line[index->current];
    if (index->current != 0 && ft_isspace(line[index->current - 1]) == true)
        index->previous = index->current;
    index->current++;
    while (line[index->current] != tmp && line[index->current] != '\0')
        index->current++;
    if (line[index->current] == '\0')
        return (NOT_LEXED);
    index->current++;
    return (LEXED);
}

void ft_get_next_index(char *line, t_index *index)
{
    t_dictionary dictionary;

    if (index->current == 0)
    {
        while (ft_isspace(line[index->current]) == true)
            index->current++;
        index->previous = index->current;
    }
    dictionary = ft_serach_operator(&line[index->current]);
    if (dictionary.operator_type == NO_OPERATOR && line[index->current] != '\0')
        index->current++;
}