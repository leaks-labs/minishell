#include "exec.h"
#include "heredoc.h"
#include "redirections.h"
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int			ft_exec_line(t_msh *msh, t_pipeline *pipeline);
static int	ft_init_exl(t_exl *exl, t_msh *msh, t_pipeline *pipeline);
static int	ft_exec_cmd(t_exl *exl, t_pipeline *pipeline);
static int	ft_wait(pid_t last_pid);

sig_atomic_t	g_interrupt_heredoc;

int	ft_exec_line(t_msh *msh, t_pipeline *pipeline)
{
	t_exl	s_exl;
	int		exit_code;

	if (ft_init_exl(&s_exl, msh, pipeline) == -1)
	{
		if (g_interrupt_heredoc > 0)
			return (128 + g_interrupt_heredoc);
		return (1);
	}
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
	g_interrupt_heredoc = 0;
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
		if (WIFSIGNALED(wstatus))
		{
			exit_status = 128 + WTERMSIG(wstatus);
			if (exit_status == 128 + SIGQUIT)
				printf("Quit: %d", SIGQUIT);
			printf("\n");
		}
		else if (WIFEXITED(wstatus))
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
