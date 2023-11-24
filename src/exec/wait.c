/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:30 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:55:31 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	sig_value;

	waitpid(last_pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
	{
		sig_value = WTERMSIG(wstatus);
		exit_status = 128 + sig_value;
		if (sig_value == SIGQUIT)
			printf("Quit: %d", SIGQUIT);
		if (sig_value == SIGINT || sig_value == SIGQUIT)
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
		if (WIFSIGNALED(wstatus) \
			&& (WTERMSIG(wstatus) == SIGINT || WTERMSIG(wstatus) == SIGQUIT))
			*print_nl = true;
}
