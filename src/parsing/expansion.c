#include "parse.h"
#include "lexer.h"
#include "exec.h"
#include "utils.h"
#include "stdlib.h"
#include <stdio.h> //check

char    *ft_expansion_monitor(t_msh *msh, char *src, bool handle_quote);
uint8_t ft_get_expansion_list(t_list_node **expansion_list, char *src);

char    *ft_expansion_monitor(t_msh *msh, char *src, bool handle_quote)
{
    (void)msh;
    (void)handle_quote;
    t_list_node *expansion_list;
    char        *dst = NULL;

    expansion_list = NULL;
    if (ft_get_expansion_list(&expansion_list, src) == 1)
    {
        ft_lstclear(&expansion_list, NULL);
        return (NULL);
    }
    while (expansion_list != NULL)
    {
         printf("exp:%s.\n", (char *)expansion_list->content);
        expansion_list = expansion_list->next;
    }
    ft_lstclear(&expansion_list, NULL); //leastclear pares avoir fait dst
    return (dst);
}

uint8_t ft_get_expansion_list(t_list_node **expansion_list, char *src)
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
        if (src[index.current] != '\0')
        {
            printf("char:%c.\n", src[index.current]);
            index.current++;
        }
    }
    if (index.previous != index.current)
        if (ft_tokenise_expansion(expansion_list, &index, src) == 1)
            return (1);
    return (0);
}
