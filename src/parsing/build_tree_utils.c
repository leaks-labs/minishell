#include "parse.h"
#include "utils.h"

size_t ft_pipeline_len(t_token_container *token_container);
bool ft_is_redirection(t_lexer_operator e_operator_type);
void ft_reset_args(t_pl_args *pl_args);
void ft_set_args(t_token_list *token_node, t_pl_args *pl_args);
uint8_t ft_alloc_args(t_pl *pipeline, t_pl_args *pl_args, size_t i);
t_io_type ft_enum_swap(t_lexer_operator e_lexer_operator);


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

bool ft_is_redirection(t_lexer_operator e_operator_type)
{
	return (e_operator_type == HERE_DOC || e_operator_type == APPEND \
			|| e_operator_type == INPUT || e_operator_type == OUTPUT);
}

void ft_reset_args(t_pl_args *pl_args)
{
	pl_args->n_args = 0;
	pl_args->n_redirect = 0;
}

void ft_set_args(t_token_list *token_node, t_pl_args *pl_args)
{
	if (ft_is_redirection(token_node->struct_token->operator_type) == true)
		pl_args->n_redirect++;
	else
		pl_args->n_args++;
}

uint8_t ft_alloc_args(t_pl *pipeline, t_pl_args *pl_args, size_t i)
{
	pipeline->cmd_list[i].args = ft_calloc(pl_args->n_args + 1, sizeof(char *));
	if (pipeline->cmd_list[i].args == NULL)
		return (1);
	if (pl_args->n_redirect > 0)
	{
		pipeline->cmd_list[i].n_redirect = pl_args->n_redirect;
		pipeline->cmd_list[i].redirect_arr = ft_calloc(pl_args->n_redirect, sizeof(t_redirect));
		if (pipeline->cmd_list[i].redirect_arr == NULL)
			return (1);
	}
	else
	{
		pipeline->cmd_list[i].n_redirect = pl_args->n_redirect;
		pipeline->cmd_list[i].redirect_arr = NULL;
	}
	return (0);
}

t_io_type ft_enum_swap(t_lexer_operator e_lexer_operator)
{
	if (e_lexer_operator == HERE_DOC)
		return (IO_HEREDOC);
	else if (e_lexer_operator == APPEND)
		return (IO_APPEND);
	else if (e_lexer_operator == INPUT)
		return (IO_INPUT);
	else
		return (IO_OUTPUT);
}