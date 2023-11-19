#include "parse.h"
#include "lexer.h"
#include <stddef.h>

uint8_t	ft_parse(t_list *env, t_pl *pipeline, char *line);

uint8_t	ft_parse(t_list *env, t_pl *pipeline, char *line)
{
	t_token_container *token_container;
	(void)pipeline;
	token_container = ft_lexer_monitor(line);
	if (token_container == NULL)
		return (1);
	if (ft_check_expansion(env, token_container) == 1) //do exp, rm quotes, gramar, build tree
	{
		ft_delete_list(token_container);
		return (1);
	}
	return (0);
}