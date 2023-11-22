#include "parse.h"
#include "lexer.h"
#include "exec.h"
#include "utils.h"
#include "stdlib.h"
#include <stdio.h> //check

char            *ft_expansion_monitor(t_msh *msh, char *src, bool handle_quote);
static uint8_t  ft_get_expansion_list(t_list_node **expansion_list, char *src);
static char     *ft_command_expand(t_msh *msh, t_list_node *expansion_list, bool handle_quote);


char    *ft_expansion_monitor(t_msh *msh, char *src, bool handle_quote)
{
    t_list_node *expansion_list;
    char        *dst;

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

static uint8_t ft_get_expansion_list(t_list_node **expansion_list, char *src)
{
    t_index     index;

    index.current = 0;
    index.previous = index.current;
    while (src[index.current] != '\0')
    {
        if (src[index.current] == '$' && index.current != index.previous)
        {
            if (ft_tokenise_expansion(expansion_list, &index, src) == 1)
                return (1);
            index.previous = index.current;
        }
        if (src[index.current] == '$' && (src[index.current + 1] == '_'
        || src[index.current + 1] == '?' || ft_isalpha(src[index.current + 1])))
        {
            if (ft_get_expansion_var(expansion_list, &index, src) == 1)
                return (1);
        }
        else if (src[index.current] != '\0')
            index.current++;
    }
    if (index.previous != index.current)
        if (ft_tokenise_expansion(expansion_list, &index, src) == 1)
            return (1);
    return (0);
}

char *ft_command_expand(t_msh *msh, t_list_node *expansion_list, bool handle_quote)
{
    char *src;
    char *dst;
    char *tmp;
    char flag;

    flag = '\0';
    dst = ft_strdup("");
    while (dst != NULL && expansion_list != NULL)
    {
        src = (char *)expansion_list->content;
        ft_get_flag(src, &flag);
        if ((handle_quote == false || flag != '\'') \
            && (src[0] == '$' \
            && (ft_strchr("_?", src[1]) || ft_isalpha(src[1]))))
        {
            src = ft_expand(msh, src);
            if (src == NULL)
                return (ft_freef("%p", dst));
        }
        tmp = dst;
        dst = ft_join(2, dst, src);
        ft_freef("%p", tmp);
        if (src != expansion_list->content)
            free(src);
        expansion_list = expansion_list->next;
    }
    return (dst);
}
