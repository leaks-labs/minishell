#include "parse.h"
#include "utils.h"
#include <stdio.h> //attention

uint8_t	ft_build_tree(t_pl *pipeline, t_token_container *token_container);
size_t	ft_pipeline_len(t_token_container *token_container);
uint8_t	ft_alloc_pipeline(t_pl *pipeline, t_token_container *token_container);
uint8_t ft_fill_pipeline(t_pl *pipeline, t_token_container *token_container);



uint8_t ft_build_tree(t_pl *pipeline, t_token_container *token_container)
{

	pipeline->n_cmd = ft_pipeline_len(token_container) + 1;
	pipeline->cmd_list = ft_calloc(pipeline->n_cmd, sizeof(t_cmd));
	if (pipeline->cmd_list == NULL)
		return (1);
	if (ft_alloc_pipeline(pipeline, token_container) == 1 \
		|| ft_fill_pipeline(pipeline, token_container) == 1)
		return (1);
	return (0);
}

uint8_t ft_alloc_pipeline(t_pl *pipeline, t_token_container *token_container)
{
	t_token_list	*token_node;
	t_pl_args		pl_args;
	size_t 			i;

	token_node = token_container->sentinel_node->next;
	i = 0;
	while (i < pipeline->n_cmd)
	{
		ft_reset_args(&pl_args);
		while (token_node->node_type != SENTINEL_NODE \
		&& token_node->struct_token->operator_type != PIPE)
		{
			ft_set_args(token_node, &pl_args);
			token_node = token_node->next;
		}
		token_node = token_node->next;
		if (ft_alloc_args(pipeline, &pl_args, i) == 1) //if == 2 protect ?
			return (1);
		++i;
	}
	return (0);
}

		
uint8_t ft_fill_pipeline(t_pl *pipeline, t_token_container *token_container)
{
	t_token_list *token_node;
	size_t i;
	size_t j;
	size_t k = 0;

	i = 0;
	token_node = token_container->sentinel_node->next;
	while (i < pipeline->n_cmd)
	{
		j = 0;
		k = 0;
		while (token_node->node_type != SENTINEL_NODE \
			&& token_node->struct_token->operator_type != PIPE)
		{
			if (ft_is_redirection(token_node->struct_token->operator_type) == true)
			{
				pipeline->cmd_list[i].redirect_arr[j].file = ft_strdup(token_node->next->struct_token->token);
				if (pipeline->cmd_list[i].redirect_arr[j].file == NULL)
					return (1);
				pipeline->cmd_list[i].redirect_arr[j].e_iotype = ft_enum_swap(token_node->struct_token->operator_type);
				token_node = token_node->next;
				++j;

			}
			else
			{
				pipeline->cmd_list[i].args[k] = ft_strdup(token_node->struct_token->token);
				if (pipeline->cmd_list[i].args[k] == NULL)
					return (1);
				k++;
			}
			token_node = token_node->next;
		}
		token_node = token_node->next;
		++i;
	}
	return (0);
}