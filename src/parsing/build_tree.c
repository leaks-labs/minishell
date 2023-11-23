#include "parse.h"
#include "utils.h"
#include <stdio.h> //attention

uint8_t	ft_build_tree(t_pl *pipeline, t_token_container *token_container);
size_t	ft_pipeline_len(t_token_container *token_container);
uint8_t	ft_alloc_pipeline(t_pl *pipeline, t_token_container *token_container);
void	ft_args_len(t_token_list *token_node, t_pl_args *pl_args);
uint8_t ft_fill_pipeline(t_pl *pipeline, t_token_container *token_container);
//cat dossier

bool	ft_is_redirection(t_lexer_operator e_operator_type);

uint8_t ft_build_tree(t_pl *pipeline, t_token_container *token_container)
{
	uint8_t	exit_status;

	pipeline->n_cmd = ft_pipeline_len(token_container) + 1;
	printf("%zu", pipeline->n_cmd);
	pipeline->cmd_list = ft_calloc(pipeline->n_cmd, sizeof(t_cmd));
	exit_status = ft_alloc_pipeline(pipeline, token_container);
	exit_status = ft_fill_pipeline(pipeline, token_container);


	exit_status = 0;
	printf("test\n");
	return (exit_status);
}

size_t ft_pipeline_len(t_token_container *token_container)
{
	t_token_list	*token_node;
	size_t			n_cmd;

	n_cmd = 0;
	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
		if (token_node->struct_token->operator_type != NO_OPERATOR \
			&& token_node->struct_token->operator_type == PIPE)
			++n_cmd;
		token_node = token_node->next;
	}
	return (n_cmd);
}

uint8_t ft_alloc_pipeline(t_pl *pipeline, t_token_container *token_container)
{
	t_token_list *token_node;
	t_pl_args		pl_args;
	size_t 			i;

	i = 0;
	token_node = token_container->sentinel_node->next; //always the same pipe
	while (i < pipeline->n_cmd)
	{
		pl_args.n_args = 0;
		pl_args.n_redirect = 0;
		ft_args_len(token_node, &pl_args);
		token_node = token_container->sentinel_node->next; //always the same pipe
		printf("n_args :%zu\n",pl_args.n_args);
		pipeline->cmd_list[i].args = ft_calloc(pl_args.n_args + 1, sizeof(char *));
		if (pl_args.n_redirect > 0)
		{
			pipeline->cmd_list[i].n_redirect = pl_args.n_redirect;
			pipeline->cmd_list[i].redirect_arr = ft_calloc(pl_args.n_redirect, sizeof(t_redirect));
		}
		else
		{
			pipeline->cmd_list[i].n_redirect = pl_args.n_redirect;
			pipeline->cmd_list[i].redirect_arr = NULL;
		}
		++i;
	}
	return (0);
}

void	ft_args_len(t_token_list *token_node, t_pl_args *pl_args) //cat dossier
{
	while (token_node->node_type != SENTINEL_NODE \
		&& token_node->struct_token->operator_type != PIPE)
	{
		if (ft_is_redirection(token_node->struct_token->operator_type) == true)
			pl_args->n_redirect++;
		else
			pl_args->n_args++;
		token_node = token_node->next;
	}
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

bool ft_is_redirection(t_lexer_operator e_operator_type)
{
	return (e_operator_type == HERE_DOC || e_operator_type == APPEND
			|| e_operator_type == INPUT || e_operator_type == OUTPUT);
}