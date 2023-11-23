#include "parse.h"
#include "lexer.h"
#include "exec.h"
#include "utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> //attention

t_parse	ft_parse(t_msh *msh, t_pl *pipeline, char *line);

void ft_quoting(t_token_container *token_container);
uint8_t ft_check_grammar(t_token_container *token_container);
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
	exit_status = ft_check_grammar(token_container);  //end of list
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
	ft_delete_list(token_container);
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

