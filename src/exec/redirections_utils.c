#include "exec.h"

int		ft_createpipe(int *pp);
void	ft_close_used_pipes(t_fd_io *fd_io);
bool	ft_islastcmd(t_exl *exl);

int	ft_createpipe(int *pp)
{
	if (pipe(pp) == -1)
	{
		// perror("pipe creation");
		pp[0] = -1;
		pp[1] = -1;
		return (-1);
	}
	return (0);
}

void	ft_close_used_pipes(t_fd_io *fd_io)
{
	if (fd_io->fd_to_read != STDIN_FILENO)
		close(fd_io->fd_to_read);
	if (fd_io->fd_to_write != STDOUT_FILENO)
		close(fd_io->fd_to_write);
}

bool	ft_islastcmd(t_exl *exl)
{
	return (exl->cmd_idx == exl->n_cmd - 1);
}
