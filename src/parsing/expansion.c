#include "parse.h"
#include "lexer.h"
#include "utils.h"
#include "stdlib.h"
#include <stdio.h>

uint8_t ft_check_expansion(t_list *env, t_token_container *token_container);
char    *ft_get_expansion(t_list *env, char *src, bool handle_quote);


uint8_t ft_check_expansion(t_list *env, t_token_container *token_container)
{
	t_token_list *token_node;

        printf("line 15\n\n");

	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
		if (token_node->struct_token->operator_type == NO_OPERATOR && ft_strchr(token_node->struct_token->token, '$'))
            if (ft_expansion_monitor(env, token_node->struct_token->token, true) == NULL)
                return (1);

	    token_node = token_node->next;
	}
    return (0);
}

char    *ft_expansion_monitor(t_list *env, char *src, bool handle_quote)
{
    char    *dst;

    if (handle_quote == true)
        dst = ft_expansion_quoting(env, src);
    else
        dst = ft_expansion(env, src);
    return (dst);
}

char *ft_expansion_quoting(t_list *env, char *src)
{
    char    *dst;
    char    *tmp;
    t_index index;

    dst = ft_strdup(src);
    index.current = 0;
    index.previous = index.current;
    while (dst != NULL && dst[index.current] != '\0')
    {
        if (dst[index.current] == '$')  //dols endl
        {
            if (dst[index.current + 1] == '_' || ft_isalpha(dst[index.current + 1]) == true)
            {
                tmp = ft_substr(dst, (unsigned int)index.previous, index.current - 1);
            }
        }
    }
    return (dst);
}

    //i = 0;
    // while (src[i] != '\0')
    // {
    //     if (src[i] == '$')
    //     {
    //         j = 1;
    //         if (src[i + j] == '_' || ft_isalpha(src[i + j]) == true)
    //         {
    //             while (src[i + j] == '_' || ft_isalnum(src[i + j]))
    //                 ++j;
    //             char *str = ft_substr(src, (unsigned int)i + 1, j);
    //             char *str2 = ft_strdup(ft_getenv(str, env));
    //             dst = ft_join(2, dst, str2);
    //             i += ft_strlen(str2);
    //         }
            
    //     }
    //     tmp[0] = src[i];
    //     dst = ft_join(2, dst, tmp);
    //     printf(":%s.", dst);
    //     ++i;
    // }
    return (dst);