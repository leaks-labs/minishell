#include "exec.h"
#include "msh_signal.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_run(t_msh *msh);

void	ft_run(t_msh *msh)
{
	t_pipeline	s_pipeline;
	char		*line;

	while (true)
	{
		ft_set_signals(MSH_SIG_REPROMPT);
		++msh->line_num;
		line = readline(PROMPT);
		ft_set_signals(MSH_SIG_IGN);
		if (line == NULL)
			return ;
		if (*line != '\0')
		{
			add_history(line);
			msh->exit_status = ft_parse(&s_pipeline, line);
			if (msh->exit_status == PARSE_SUCCESS)
				msh->exit_status = ft_exec_line(msh, &s_pipeline);
		}
		free(line);
	}
	free(line);
	rl_clear_history();
	return ;
}
