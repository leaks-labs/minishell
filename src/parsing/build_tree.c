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
		return (2);
	if (ft_alloc_pipeline(pipeline, token_container) == 2 \
		|| ft_fill_pipeline(pipeline, token_container) == 2)
		return (2);
	printf("pass tree\n");
	return (0);
}

uint8_t ft_alloc_pipeline(t_pl *pipeline, t_token_container *token_container)
{
	t_token_list *token_node;
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
			printf("[%s]\n", token_node->struct_token->token);
			token_node = token_node->next;
		}
		token_node = token_node->next;
		ft_alloc_args(pipeline, &pl_args, i); //if == 2 protect ?
		printf("n_args :%zu\n",pl_args.n_args);
		++i;
	}
	return (0);
}

		
uint8_t ft_fill_pipeline(t_pl *pipeline, t_token_container *token_container)
{
	t_token_list *token_node;
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	token_node = token_container->sentinel_node->next;
	while (i < pipeline->n_cmd) //fill array
	{
		j = 0;
		while (token_node->node_type != SENTINEL_NODE \
			&& token_node->struct_token->operator_type != PIPE) //update adr so it's not always the same node
		{
			if (ft_is_redirection(token_node->struct_token->operator_type) == true)
			{
				//pipeline->cmd_list[i].redirect_arr[j].file = ft_strdup//(token_node->next->struct_token->token);
				//if ()
			
			}
			else
			{
				pipeline->cmd_list[i].args[j] = ft_strdup(token_node->struct_token->token);
				if (pipeline->cmd_list[i].args[j] == NULL)
					return (2); //2?
			}
			token_node = token_node->next;
			++j;
		}
		token_node = token_node->next;
		++i;
	}
	return (0);
}