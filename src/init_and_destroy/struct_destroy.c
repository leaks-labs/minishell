#include "init.h"
#include "env.h"
#include "list.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int		ft_quit(t_msh *msh);
void	ft_free_cmd_list(t_pl *pipeline);

int	ft_quit(t_msh *msh)
{
	int	exit_cpy;

	exit_cpy = msh->exit_status;
	ft_lstclear(&msh->env.list_node, &ft_free_content);
	ft_freef("%P%p%p", msh->path, msh->cwd, msh);
	rl_clear_history();
	return (exit_cpy);
}

void	ft_free_cmd_list(t_pl *pipeline)
{
	t_cmd	*cmd;
	ssize_t	i;
	ssize_t	j;

	cmd = pipeline->cmd_list;
	i = -1;
	while (++i < pipeline->n_cmd)
	{
		ft_freef("%P", cmd[i].args);
		j = -1;
		while (++j < cmd[i].n_redirect)
			free(cmd[i].redirect_arr[j].file);
		free(cmd[i].redirect_arr);
	}
	free(cmd);
	pipeline->cmd_list = NULL;
	pipeline->n_cmd = 0;
}
