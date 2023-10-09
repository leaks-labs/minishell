#include "exec.h"
#include "redirections.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void			ft_child_process(t_exl *exl, t_cmd *cmd);
static uint8_t	ft_get_err_code(char *cmd);

void	ft_child_process(t_exl *exl, t_cmd *cmd)
{
	char	*path_cmd;
	uint8_t	err_code;

	err_code = ft_apply_redirections(exl);
	// perror() ??
	if (err_code == 0)
	{
		if (cmd->args != NULL)
		{
			path_cmd = ft_get_cmd_path(exl->path, cmd->args[0]);
			if (path_cmd != NULL)
				execve(path_cmd, cmd->args, exl->env);
			err_code = ft_get_err_code(cmd->args[0]);
			free(path_cmd);
		}
	}
	ft_close_used_pipes(&exl->s_fd_io);
	ft_freef("%P", exl->path);
	// free other struct extern to exl (like pipeline, msh, ...)
	exit(err_code);
}

static uint8_t	ft_get_err_code(char *cmd)
{
	if (errno == ENOENT)
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
}
