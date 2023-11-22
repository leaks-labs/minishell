#include "exec.h"
#include "msh_signal.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void		ft_run(t_msh *msh);
static char	*ft_prompt(t_msh *msh);

volatile sig_atomic_t	g_signal_value;

void	ft_run(t_msh *msh)
{
	t_pl			s_pipeline;
	char			*line;
	t_parse_return	e_parse_return;

	g_signal_value = 0;
	while (true)
	{
		line = ft_prompt(msh);
		if (line == NULL)
			return ;
		g_signal_value = 0;
		if (*line != '\0')
		{
			add_history(line);
			e_parse_return = ft_parse(&s_pipeline, line);
			free(line);
			if (e_parse_return == PARSE_SUCCESS)
				msh->exit_status = ft_exec_line(msh, &s_pipeline);
		}
		else
			free(line);
	}
}

static char	*ft_prompt(t_msh *msh)
{
	char	*line;

	ft_set_signals(MSH_SIG_REPROMPT);
	++msh->line_num;
	line = readline(PROMPT);
	ft_set_signals(MSH_SIG_IGN);
	return (line);
}
