#include "parse.h"
#include "lexer.h"
#include "exec.h"
#include "utils.h"
#include "stdlib.h"

#include <stdio.h>

uint8_t ft_check_expansion(t_msh *msh, t_token_container *token_container);
uint8_t ft_get_expansion_var(t_list_node **expansion_list, t_index *index, char *src);
uint8_t ft_tokenise_expansion(t_list_node **node, t_index *index, char *src);

uint8_t ft_check_expansion(t_msh *msh, t_token_container *token_container)
{
	t_token_list *token_node;

	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
        if (token_node->struct_token->operator_type == NO_OPERATOR 
        && (token_node->prev->struct_token == NULL 
        || token_node->prev->struct_token->operator_type != HERE_DOC)
        && ft_strchr(token_node->struct_token->token, '$'))
                    if (ft_expansion_monitor(msh,
                    token_node->struct_token->token, true) == NULL)
                        return (1);
	    token_node = token_node->next;
	}
    return (0);
}

uint8_t ft_get_expansion_var(t_list_node **expansion_list, t_index *index, char *src)
{
    index->current++;
    if (src[index->current] == '?')
    {
        index->current++;
        if (ft_tokenise_expansion(expansion_list, index, src) == 1)
            return (1);
        index->previous = index->current;

    }
    else
    {
        while((src[index->current] == '_' || ft_isalnum(src[index->current])))
            index->current++;
        if (ft_tokenise_expansion(expansion_list, index, src) == 1)
            return (1);
        index->previous = index->current;
    }
    return (0);
}

uint8_t ft_tokenise_expansion(t_list_node **node, t_index *index, char *src)
{
    t_list_node *new_node;

    char *str = ft_substr(src, (unsigned int)index->previous, index->current - index->previous);
    printf(":%s.\n", str);
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