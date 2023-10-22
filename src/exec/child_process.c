#include "exec.h"
#include "redirections.h"
#include "msh_signal.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t		ft_child_process(t_exl *exl, t_cmd *cmd);
static int	ft_launch_extern_cmd(t_exl *exl, char **args);
static int	ft_get_err_code(char *cmd);

pid_t	ft_child_process(t_exl *exl, t_cmd *cmd)
{
	const pid_t	pid = fork();
	int			err_code;

	// if (pid == -1)
	// 	perror("fork error");
	if (pid != 0)
		return (pid);
	err_code = 0;
	if (ft_set_redirections(exl, cmd) != 0 || ft_apply_redirections(exl) != 0)
		err_code = 1;
	if (err_code == 0 && cmd->args != NULL)
		err_code = ft_launch_extern_cmd(exl, cmd->args);
	ft_close_used_pipes(&exl->s_fd_io);
	// free other struct extern to exl (like pipeline, msh, history, line...) ??
	exit(err_code);
}

static int	ft_launch_extern_cmd(t_exl *exl, char **args)
{
	char	*cmd_path;

	cmd_path = ft_get_cmd_path(exl->path, args[0]);
	if (cmd_path != NULL)
	{
		// is it in the right place? Better to be earlier?
		ft_set_signals(MSH_SIG_EXT_CMD);
		execve(cmd_path, args, exl->env);
		ft_set_signals(MSH_SIG_IGN);
	}
	free(cmd_path);
	return (ft_get_err_code(args[0]));
}

static int	ft_get_err_code(char *cmd)
{
	if (errno == ENOENT || errno == ENAMETOOLONG)
	{
		ft_putstr_fd(MSH_ERROR_PROMPT, STDERR_FILENO);
		if (ft_isapath(cmd) == true)
			perror(cmd);
		else
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
	// need to print error (perror()) for other error types?
}
