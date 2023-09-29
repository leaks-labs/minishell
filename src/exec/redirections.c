#include "exec.h"

int				ft_set_redirections(t_exl *exl, t_cmd *cmd);
uint8_t			ft_apply_redirections(t_exl *exl);
static void		ft_default_redirections(t_exl *exl);

int	ft_set_redirections(t_exl *exl, t_cmd *cmd)
{
	int			(*f[4])(t_exl *, char *);
	t_redirect	*current_redirect;
	ssize_t		i;

	ft_default_redirections(exl);
	(f)[INPUT] = &ft_set_input;
	(f)[HEREDOC] = &ft_set_heredoc;
	(f)[OUTPUT] = &ft_set_output;
	(f)[APPEND] = &ft_set_append;
	i = -1;
	current_redirect = cmd->redirect_arr;
	while (++i < cmd->n_redirect)
	{
		if ((f)[current_redirect->e_iotype](exl, current_redirect->file) == -1)
		{
			while (++i < cmd->n_redirect)
				if ((++current_redirect)->e_iotype == HEREDOC)
					exl->hd.hd_list = ft_delete_front_hd_node(exl->hd.hd_list);
			return (-1);
		}
		++current_redirect;
	}
	return (0);
}

uint8_t	ft_apply_redirections(t_exl *exl)
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
	return (res[0] == -1 || (ft_islastcmd(exl) == false && res[1] == -1));
}

static void	ft_default_redirections(t_exl *exl)
{
	if (exl->cmd_idx == 0)
		exl->pipe[0] = STDIN_FILENO;
	exl->s_fd_io.fd_to_read = exl->pipe[0];
	if (ft_islastcmd(exl) == false)
		ft_createpipe(exl->pipe);
	else
		exl->pipe[1] = STDOUT_FILENO;
	exl->s_fd_io.fd_to_write = exl->pipe[1];
}
