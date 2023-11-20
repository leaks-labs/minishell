#include "parse.h"
#include "lexer.h"
#include "exec.h"
#include "utils.h"
#include "stdlib.h"
#include <stdio.h>

uint8_t ft_check_expansion(t_msh *msh, t_token_container *token_container);
char    *ft_expansion_monitor(t_msh *msh, char *src, bool handle_quote);
char    *ft_get_expansion_list(char *src);
char    *ft_tokenise_expansion(t_list_node **node, t_index *index, char *src);


uint8_t ft_check_expansion(t_msh *msh, t_token_container *token_container)
{
	t_token_list *token_node;

	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
        if (token_node->struct_token->operator_type == NO_OPERATOR 
        && (token_node->prev->struct_token == NULL || token_node->prev->struct_token->operator_type != HERE_DOC)
        && ft_strchr(token_node->struct_token->token, '$'))
                    if (ft_expansion_monitor(msh, token_node->struct_token->token, true) == NULL)
                        return (1);

	    token_node = token_node->next;
	}
    return (0);
}

char    *ft_expansion_monitor(t_msh *msh, char *src, bool handle_quote)
{
    t_list_node *expansion_list;
    char        *dst = NULL;

    expansion_list = ft_lstnew(NULL);
    if (ft_get_expansion_list(src) == false)
    {
        ft_lstclear(&expansion_list, NULL);
        return (NULL);
    }
    return (dst);
}

char *ft_get_expansion_list(char *src)
{
    t_list_node *node;
    t_index     index;

    index.current = 0;
    index.previous = index.current;
    while (src[index.current] != '\0')
    {
        if (src[index.current] == '$' && index.current != index.previous)
        {
            char *str = ft_substr(src, (unsigned int)index.previous, index.current - index.previous);
            printf("before:%s.\n", str);
            index.previous = index.current;
            //tokenise before dols
        }
        if (src[index.current] == '$' && (src[index.current + 1] == '_' || ft_isalpha(src[index.current + 1]) == true))
        {
            index.current++;
            while(src[index.current] == '_' || ft_isalpha(src[index.current]) == true) //ou '?'
                index.current++;
            char *str = ft_substr(src, (unsigned int)index.previous, index.current - index.previous);
            printf("exp:%s.\n", str);
            index.previous = index.current;
            //tokenise after dols
        }
        if (src[index.current] != '\0')
            index.current++;
    }
    if (index.previous != index.current)
    {
        if (ft_tokenise_expansion(&node, &index, src) == NULL)
            ft_lstclear(&node, NULL);
    }
    return (node);
}

char *ft_tokenise_expansion(t_list_node **node, t_index *index, char *src)
{
    t_list_node *new_node;

    char *str = ft_substr(src, (unsigned int)index->previous, index->current - index->previous);
    new_node = ft_lstnew(str);
    if (new_node == NULL || str == NULL)
    {
        free(str);
    }
    ft_lstadd_back(node, new_node);
    

}
