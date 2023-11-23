#include "parse.h"
#include "utils.h"

void	ft_quoting(t_token_container *token_container)
{
	t_token_list	*token_node;
	t_token_list	*tmp_node;

	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
		if (token_node->struct_token->operator_type == NO_OPERATOR
			&& *token_node->struct_token->token == '\0')
		{
			tmp_node = token_node->next;
			ft_delete_node(token_container, token_node);
			token_node = tmp_node;
		}
		else if (token_node->node_type != SENTINEL_NODE
			&& token_node->struct_token->operator_type == NO_OPERATOR
			&& (ft_strchr(token_node->struct_token->token, '"')
				|| ft_strchr(token_node->struct_token->token, '\'')))
		{
			ft_rm_quotes(token_node->struct_token->token);
			token_node = token_node->next;
		}
		else
			token_node = token_node->next;
	}
}
