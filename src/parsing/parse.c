#include "parse.h"
#include "lexer.h"
#include "exec.h"
#include "utils.h"
#include <stddef.h>

#include <stdio.h> //attention

uint8_t	ft_parse(t_msh *msh, t_pl *pipeline, char *line);

uint8_t	ft_parse(t_msh *msh, t_pl *pipeline, char *line)
{
	(void)pipeline;
	t_token_container *token_container;
	token_container = ft_lexer_monitor(line);
	if (token_container == NULL)
		return (1);
	t_token_list *node = token_container->sentinel_node->next;
	while (node->node_type != SENTINEL_NODE)
	{
		printf("%s\n\n", node->struct_token->token);
		node = node->next;
	}
	if (ft_check_expansion(msh, token_container) == 1 || ft_quoting(token_container) == 1 || ft_check_gramar(token_container) == 1) //do exp, rm quotes, gramar, build tree
	{
		ft_delete_list(token_container);
		return (1);
	}
	printf("here\n");
	return (0);
}

uint8_t ft_quoting(t_token_container *token_container)
{
	t_token_list *token_node;

	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
		if (token_node->struct_token->operator_type == NO_OPERATOR
		&& (ft_strchr(token_node->struct_token->token, '"')
		|| ft_strchr(token_node->struct_token->token, '\'')))
		{
			ft_rm_quotes(token_node->struct_token->token);
		}
		token_node = token_node->next;
	}
	return (0);
}

uint8_t ft_check_gramar(t_token_container *token_container)
{
	t_token_list *token_node;

	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
		if (token_node->prev->struct_token != NULL 
		|| (token_node->prev->struct_token->operator_type != NO_OPERATOR 
		&& token_node->struct_token->operator_type != NO_OPERATOR))
		token_node = token_node->next;
	}
	return (0);
}