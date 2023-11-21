#include "parse.h"
#include "lexer.h"
#include "exec.h"
#include "utils.h"
#include "stdlib.h"
#include <stdio.h> //check

char            *ft_expansion_monitor(t_msh *msh, char *src, bool handle_quote);
static uint8_t  ft_get_expansion_list(t_list_node **expansion_list, char *src);
static char     *ft_list_to_var(t_msh *msh, t_list_node *expansion_list, bool handle_quote);

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
    dst = ft_list_to_var(msh, expansion_list, handle_quote);
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

static char *ft_list_to_var(t_msh *msh, t_list_node *expansion_list, bool handle_quote)
{
    (void)handle_quote;
    char *dst = ft_strdup("");
    char *tmp;
    size_t i;
    char buf[3];
    i = 0;
    while (expansion_list != NULL)
    {
        tmp = (char *)expansion_list->content;
        if (tmp[i] == '$' && (tmp[i + 1] == '_'
        || tmp[i + 1] == '?' || ft_isalpha(tmp[i + 1]))) //quoting or not
        {
            if (tmp[i + 1] == '?')
            {
                ft_uimaxtostr(buf, 3, msh->exit_status);
                printf("%s\n", buf);
                tmp = buf;
            }
            else
            {
                tmp = ft_getenv(&tmp[i + 1], &msh->env); //dup to avoid memory corruption
                if (tmp != NULL)
                    tmp = ft_strdup(tmp);
                else
                    tmp = ft_strdup("");
            }
        }
        dst = ft_join(2, dst, tmp);
        printf("dst:%s.\n", dst);
        expansion_list = expansion_list->next;
    }
    return(dst);
}
