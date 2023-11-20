#include "parse.h"
#include "lexer.h"
#include "exec.h"
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
		printf("tok:%s.\n\n", node->struct_token->token);
		node = node->next;
	}
	if (ft_check_expansion(msh, token_container) == 1) //do exp, rm quotes, gramar, build tree
	{
		ft_delete_list(token_container);
		return (1);
	}
	printf("here\n");
	return (0);
}