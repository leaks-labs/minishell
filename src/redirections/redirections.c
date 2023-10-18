#include "heredoc.h"
#include "redirections.h"
#include <unistd.h>

int			ft_default_redirections(t_exl *exl);
int			ft_set_redirections(t_exl *exl, t_cmd *cmd);
int			ft_apply_redirections(t_exl *exl);
static bool	ft_islastcmd(t_exl *exl);

int	ft_default_redirections(t_exl *exl)
{
	int	err_code;

	err_code = 0;
	if (exl->cmd_idx == 0)
		exl->pipe[0] = STDIN_FILENO;
	exl->s_fd_io.fd_to_read = exl->pipe[0];
	if (ft_islastcmd(exl) == false)
		err_code = ft_createpipe(exl->pipe);
	else
		exl->pipe[1] = STDOUT_FILENO;
	exl->s_fd_io.fd_to_write = exl->pipe[1];
	return (err_code);
}

int	ft_set_redirections(t_exl *exl, t_cmd *cmd)
{
	int			(*f[4])(t_exl *, char *);
	t_redirect	*current_redirect;
	ssize_t		i;

	(f)[INPUT] = &ft_set_input;
	(f)[HEREDOC] = &ft_set_heredoc;
	(f)[OUTPUT] = &ft_set_output;
	(f)[APPEND] = &ft_set_append;
	i = -1;
	current_redirect = cmd->redirect_arr;
	while (++i < cmd->n_redirect)
	{
		if ((f)[current_redirect->e_iotype](exl, current_redirect->file) == -1)
			return (-1);
		++current_redirect;
	}
	return (0);
}

int	ft_apply_redirections(t_exl *exl)
{
	int	res[2];

	if (exl->s_fd_io.fd_to_read != STDIN_FILENO)
	{
		res[0] = dup2(exl->s_fd_io.fd_to_read, STDIN_FILENO);
		close(exl->s_fd_io.fd_to_read);
	}
	if (exl->s_fd_io.fd_to_write != STDOUT_FILENO)
	{
		res[1] = dup2(exl->s_fd_io.fd_to_write, STDOUT_FILENO);
		close(exl->s_fd_io.fd_to_write);
	}
	if (ft_islastcmd(exl) == false)
		close(exl->pipe[0]);
	if (res[0] == -1 || (ft_islastcmd(exl) == false && res[1] == -1))
	{
		// perror() ??
		return (-1);
	}
	return (0);
}

static bool	ft_islastcmd(t_exl *exl)
{
	return (exl->cmd_idx == exl->n_cmd - 1);
}
