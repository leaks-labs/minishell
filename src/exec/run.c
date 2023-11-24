/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:26 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:55:27 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_pl	s_pipeline;
	char	*line;
	t_parse	e_parse_return;

	s_pipeline.cmd_list = NULL;
	s_pipeline.n_cmd = 0;
	g_signal_value = 0;
	while (true)
	{
		line = ft_prompt(msh);
		if (line == NULL)
			ft_exit(msh, &s_pipeline, NULL);
		g_signal_value = 0;
		if (*line != '\0')
		{
			add_history(line);
			e_parse_return = ft_parse(msh, &s_pipeline, line);
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
