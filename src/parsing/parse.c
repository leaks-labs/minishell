#include "parse.h"
#include "lexer.h"
#include "exec.h"
#include "utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> //attention

t_parse	ft_parse(t_msh *msh, t_pl *pipeline, char *line);

void ft_quoting(t_token_container *token_container);
uint8_t ft_check_gramar(t_token_container *token_container);
uint8_t ft_build_tree(t_pl *pipeline, t_token_container *token_container);


t_parse	ft_parse(t_msh *msh, t_pl *pipeline, char *line)
{
	t_token_container *token_container;
	uint8_t exit_status;

	token_container = ft_lexer_monitor(line);
	if (token_container == NULL)
		return (PARSE_ERROR); //set msh
	if (token_container->list_size == 0)
	{
		ft_delete_list(token_container);
		return (NOTHING_TO_PARSE);
	}
	if (ft_check_expansion(msh, token_container) == 1)
	{
		ft_delete_list(token_container);
		return (PARSE_ERROR); //set msh
	}
	ft_quoting(token_container);
	exit_status = ft_check_gramar(token_container);
	if (exit_status > 0)
	{
		msh->exit_status = exit_status;
		ft_delete_list(token_container);
		return (PARSE_ERROR);
	}
	exit_status = ft_build_tree(pipeline, token_container);
	if (exit_status > 0)
	{
		msh->exit_status = exit_status;
		ft_delete_list(token_container);
		return (PARSE_ERROR);
	}
	// t_token_list *node = token_container->sentinel_node->next;
	// while (node->node_type != SENTINEL_NODE)
	// {
	// 	printf("[%s]\n", node->struct_token->token);
	// 	node = node->next;
	// }
	ft_delete_list(token_container);
	//printf("here\n");
	return (PARSE_SUCCESS);
}

void ft_quoting(t_token_container *token_container)
{
	t_token_list *token_node;
	t_token_list *tmp_node;

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

uint8_t ft_check_gramar(t_token_container *token_container)
{
	t_token_list *token_node;

	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE)
	{
		if (token_node->struct_token->operator_type != NO_OPERATOR)
		{
			if (token_node->struct_token->operator_type == PIPE)
			{
				if (token_node->prev->struct_token == NULL || token_node->prev->struct_token->operator_type != NO_OPERATOR || token_node->next->struct_token == NULL )
				{
					ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
					ft_putstr_fd(token_node->struct_token->token, 2);
					ft_putendl_fd("'", 2);
					return (2);
				}
			}
			else if (token_node->next->struct_token == NULL)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd("newline", 2);
				ft_putendl_fd("'", 2);
				return (2);
			}
			else if (token_node->next->struct_token->operator_type != NO_OPERATOR)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd(token_node->next->struct_token->token, 2);
				ft_putendl_fd("'", 2);
				return (2);
			}
			


		} 
		token_node = token_node->next;
	}
	return (0);
}

uint8_t ft_build_tree(t_pl *pipeline, t_token_container *token_container)
{
	t_token_list	*token_node;
	size_t			i;
	size_t			j;
	size_t			n_args;
	size_t			n_redirect;

	i = 0;
	j = 0;
	n_args = 0;
	n_redirect = 0;
	pipeline->n_cmd = 1;
	token_node = token_container->sentinel_node->next;
	while (token_node->node_type != SENTINEL_NODE) //find n_cmd
	{
		if (token_node->struct_token->operator_type != NO_OPERATOR
			&& token_node->struct_token->operator_type == PIPE)
				++pipeline->n_cmd;

		token_node = token_node->next;
	}
	pipeline->cmd_list = ft_calloc(pipeline->n_cmd, sizeof(t_cmd));
	printf("balise\n");
	printf("n_cmd %zu\n", pipeline->n_cmd);
	while (i < pipeline->n_cmd)
	{
		token_node = token_container->sentinel_node->next;
		while (token_node->struct_token->operator_type != PIPE) //find n_args
		{
			if (token_node->struct_token->operator_type == HERE_DOC
				|| token_node->struct_token->operator_type == APPEND
				|| token_node->struct_token->operator_type == INPUT
				|| token_node->struct_token->operator_type == OUTPUT)
				++n_redirect;
			else
				++n_args;
			token_node = token_node->next;
		}
		pipeline->cmd_list[i].args = ft_calloc(n_args + 1, sizeof(char *));
		if (n_redirect > 0)
		{
			pipeline->cmd_list->n_redirect = n_redirect;
			pipeline->cmd_list[i].redirect_arr = ft_calloc(n_redirect + 1, sizeof(t_redirect));
		}
		++i;
	}
	i = 0;
	j = 0;
	while (i < pipeline->n_cmd) //fill array
	{
		token_node = token_container->sentinel_node->next;
		while (token_node->struct_token->operator_type != PIPE)
		{
			if (token_node->struct_token->operator_type == HERE_DOC
				|| token_node->struct_token->operator_type == APPEND
				|| token_node->struct_token->operator_type == INPUT
				|| token_node->struct_token->operator_type == OUTPUT)
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
			j++;
		}
		++i;
	}
	printf("test\n");
	return (0);
}