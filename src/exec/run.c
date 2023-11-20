#include "exec.h"
#include "msh_signal.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_run(t_msh *msh);

volatile sig_atomic_t	g_signal_value;

void	ft_run(t_msh *msh)
{
	t_pl	s_pipeline;
	char	*line;

	g_signal_value = 0;
	while (true)
	{
		ft_set_signals(MSH_SIG_REPROMPT);
		++msh->line_num;
		line = readline(PROMPT);
		ft_set_signals(MSH_SIG_IGN);
		if (line == NULL)
			return ;
		g_signal_value = 0;
		if (*line != '\0')
		{
			add_history(line);
			msh->exit_status = ft_parse(msh, &s_pipeline, line);
			free(line);
			if (msh->exit_status == 0)
				msh->exit_status = ft_exec_line(msh, &s_pipeline);
		}
		else
			free(line);
	}
}
