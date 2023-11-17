#include "exec.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

int			ft_wait(pid_t last_pid);
static int	ft_wait_last_child(pid_t last_pid, bool *print_nl);
static void	ft_wait_inter_children(bool *print_nl);

int	ft_wait(pid_t last_pid)
{
	int		exit_status;
	bool	print_nl;

	print_nl = false;
	if (last_pid != -1)
		exit_status = ft_wait_last_child(last_pid, &print_nl);
	else
		exit_status = 1;
	ft_wait_inter_children(&print_nl);
	if (print_nl == true)
		printf("\n");
	return (exit_status);
}

static int	ft_wait_last_child(pid_t last_pid, bool *print_nl)
{
	int	exit_status;
	int	wstatus;

	waitpid(last_pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
	{
		exit_status = 128 + WTERMSIG(wstatus);
		if (exit_status == 128 + SIGQUIT)
			printf("Quit: %d", SIGQUIT);
		*print_nl = true;
	}
	else if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	else
		exit_status = 1;
	return (exit_status);
}

static void	ft_wait_inter_children(bool *print_nl)
{
	int	wstatus;

	while (wait(&wstatus) != -1 || errno != ECHILD)
		if (WIFSIGNALED(wstatus))
			*print_nl = true;
}
