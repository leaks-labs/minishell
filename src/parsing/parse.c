#include "parse.h"
#include "utils.h"

t_parse	ft_parse(t_msh *msh, t_pl *pipeline, char *line);

t_parse	ft_parse(t_msh *msh, t_pl *pipeline, char *line)
{
	t_token_container	*token_container;
	uint8_t				exit_status;

	token_container = ft_lexer_monitor(line);
	if (token_container == NULL)
	{
		msh->exit_status = 1;
		ft_putendl_fd("minishell: parse error", 2);
		return (PARSE_ERROR);
	}
	if (token_container->list_size == 0)
	{
		ft_delete_list(token_container);
		return (NOTHING_TO_PARSE);
	}
	if (ft_check_expansion(msh, token_container) == 1)
	{
		msh->exit_status = 1;
		ft_delete_list(token_container);
		return (PARSE_ERROR);
	}
	ft_quoting(token_container);
	if (token_container->list_size == 0)
	{
		ft_delete_list(token_container);
		return (NOTHING_TO_PARSE);
	}
	exit_status = ft_check_grammar(token_container);
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
