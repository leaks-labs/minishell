#include "exec.h"
#include "heredoc.h"
#include "redirections.h"
#include <errno.h>
#include <stddef.h>
#include <sys/wait.h>

int			ft_exec_line(t_msh *msh, t_pipeline *pipeline);
static int	ft_init_exl(t_exl *exl, t_msh *msh, t_pipeline *pipeline);
static int	ft_exec_cmd(t_exl *exl, t_pipeline *pipeline);
static int	ft_wait(pid_t last_pid);

int	ft_exec_line(t_msh *msh, t_pipeline *pipeline)
{
	t_exl	s_exl;
	int		exit_code;

	#include "utils.h"
	pipeline->cmd_list = ft_calloc(1, sizeof(t_cmd));
	pipeline->n_cmd = 1;
	pipeline->cmd_list->n_redirect = 1;
	pipeline->cmd_list->args = ft_split("wc", ' ');
	pipeline->cmd_list->redirect_arr = ft_calloc(1, sizeof(t_redirect));
	pipeline->cmd_list->redirect_arr->file = ft_strdup("eof");
	pipeline->cmd_list->redirect_arr->e_iotype = HEREDOC;

	if (ft_init_exl(&s_exl, msh, pipeline) == -1)
		return (1);
	exit_code = ft_exec_cmd(&s_exl, pipeline);
	// free other struct extern to exl (like pipeline) ??
	return (exit_code);
}

static int	ft_init_exl(t_exl *exl, t_msh *msh, t_pipeline *pipeline)
{
	exl->env = msh->env;
	exl->line_num = &msh->line_num;
	exl->cmd_idx = -1;
	exl->n_cmd = pipeline->n_cmd;
	return (ft_heredoc(pipeline->cmd_list, exl));
}

static int	ft_exec_cmd(t_exl *exl, t_pipeline *pipeline)
{
	t_cmd	*current_cmd;
	pid_t	last_pid;

	while (++exl->cmd_idx < exl->n_cmd)
	{
		last_pid = -1;
		current_cmd = pipeline->cmd_list + exl->cmd_idx;
		if (ft_default_redirections(exl) == 0)
			last_pid = ft_child_process(exl, current_cmd);
		ft_close_used_pipes(&exl->s_fd_io);
	}
	return (ft_wait(last_pid));
}

static int	ft_wait(pid_t last_pid)
{
	int	wstatus;
	int	exit_status;

	if (last_pid != -1)
	{
		waitpid(last_pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
		else
			exit_status = 1;
	}
	else
		exit_status = 1;
	while (wait(NULL) != -1 || errno != ECHILD)
		;
	return (exit_status);
}
