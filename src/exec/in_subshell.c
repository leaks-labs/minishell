/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:22 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/25 10:25:09 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"
#include "init.h"
#include "msh_signal.h"
#include "path.h"
#include "redirections.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int				ft_in_subshell(t_msh *msh, t_exl *exl, t_pl *pl);
static pid_t	ft_child_proc(t_msh *msh, t_exl *exl, t_pl *pl, t_cmd *cmd);
static int		ft_launch_extern_cmd(t_exl *exl, char **args);
static int		ft_get_err_code(const char *cmd, t_list_node *path);

int	ft_in_subshell(t_msh *msh, t_exl *exl, t_pl *pl)
{
	t_cmd	*current_cmd;
	pid_t	last_pid;

	while (exl->cmd_idx < exl->n_cmd)
	{
		last_pid = -1;
		current_cmd = pl->cmd_list + exl->cmd_idx;
		if (ft_default_redirections(exl) == 0)
			last_pid = ft_child_proc(msh, exl, pl, current_cmd);
		ft_close_used_pipes(&exl->s_fd_io);
		++exl->cmd_idx;
	}
	return (ft_wait(last_pid));
}

static pid_t	ft_child_proc(t_msh *msh, t_exl *exl, t_pl *pl, t_cmd *cmd)
{
	const pid_t	pid = fork();
	t_built_f	built_f;
	int			err_code;

	if (pid != 0)
		return (pid);
	err_code = 0;
	if (ft_set_redirections(exl, cmd) != 0 || ft_apply_redirections(exl) != 0)
		err_code = 1;
	if (ft_islastcmd(exl) == false && exl->pipe[0] != STDIN_FILENO)
		close(exl->pipe[0]);
	if (err_code == 0 && cmd->args != NULL)
	{
		built_f = ft_get_builtin(cmd->args[0]);
		if (built_f != NULL)
			err_code = built_f(msh, pl, cmd->args + 1);
		else
			err_code = ft_launch_extern_cmd(exl, cmd->args);
	}
	close(exl->s_fd_io.fd_to_read);
	close(exl->s_fd_io.fd_to_write);
	ft_free_cmd_list(pl);
	msh->exit_status = (uint8_t)err_code;
	exit(ft_quit(msh));
}

static int	ft_launch_extern_cmd(t_exl *exl, char **args)
{
	t_list_node	*path;
	char		*cmd_path;
	char		**export_env;
	int			err_code;

	path = ft_get_path(exl->env);
	cmd_path = ft_get_cmd_path(path, args[0]);
	if (cmd_path != NULL)
	{
		ft_mod_env2(exl->env, "_", cmd_path, ENV_EXP);
		export_env = ft_lst_to_env(exl->env);
		ft_set_signals(MSH_SIG_EXT_CMD);
		execve(cmd_path, args, export_env);
		ft_set_signals(MSH_SIG_IGN);
		ft_freef("%P", export_env);
	}
	err_code = ft_get_err_code(args[0], path);
	ft_lstclear(&path, NULL);
	free(cmd_path);
	return (err_code);
}

static int	ft_get_err_code(const char *cmd, t_list_node *path)
{
	if (errno == ENOENT || errno == ENAMETOOLONG)
	{
		ft_putstr_fd(MSH_ERROR_PROMPT, STDERR_FILENO);
		if (ft_isapath(cmd) == true || path == NULL)
			perror(cmd);
		else if (errno == ENOENT)
		{
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}
		return (COMMAND_NOT_FOUND);
	}
	else if (errno == EISDIR || errno == ENOTDIR || errno == ENOEXEC)
	{
		ft_putstr_fd(MSH_ERROR_PROMPT, STDERR_FILENO);
		perror(cmd);
		return (COMMAND_NOT_EXECUTABLE);
	}
	else
		return (EXIT_FAILURE);
}
