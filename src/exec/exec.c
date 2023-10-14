#include "exec.h"
#include "redirections.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

t_exec_return	ft_exec_line(t_msh *msh, t_pipeline *pipeline);
static pid_t	ft_exec_cmd(t_exl *exl, t_pipeline *pipeline);
static int		ft_wait(t_exl *exl);

t_exec_return	ft_exec_line(t_msh *msh, t_pipeline *pipeline)
{
	t_exl	s_exl;

	if (ft_init_exl(&s_exl, msh, pipeline) == -1)
	{
		msh->exit_status = 1;
		return (EXEC_ERROR);
	}
	while (++s_exl.cmd_idx < s_exl.n_cmd)
		s_exl.pid_last = ft_exec_cmd(&s_exl, pipeline);
	msh->exit_status = ft_wait(&s_exl);
	ft_freef("%P", s_exl.path);
	// free other struct extern to exl (like pipeline, msh, history, line...) ??
	//return different code than just EXEC_SUCCESS for builtins
	return (EXEC_SUCCESS);
}

static pid_t	ft_exec_cmd(t_exl *exl, t_pipeline *pipeline)
{
	t_cmd	*current_cmd;
	pid_t	pid;

	current_cmd = pipeline->cmd_list + exl->cmd_idx;
	pid = -1;
	if (ft_set_redirections(exl, current_cmd) == 0)
	{
		pid = fork();
		if (pid == 0)
			ft_child_process(exl, current_cmd);
		// if (pid == -1)
		// 	perror("fork error");
	}
	ft_close_used_pipes(&exl->s_fd_io);
	return (pid);
}

static int	ft_wait(t_exl *exl)
{
	int	wstatus;
	int	exit_status;

	if (exl->pid_last != -1)
	{
		waitpid(exl->pid_last, &wstatus, 0);
		if (WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
		else
			exit_status = EXIT_FAILURE;
	}
	else
		exit_status = EXIT_FAILURE;
	while (wait(NULL) != -1 || errno != ECHILD)
		;
	return (exit_status);
}
