#include "exec.h"
#include "redirections.h"
#include <unistd.h>

int			ft_in_shell(t_msh *msh, t_exl *exl, t_cmd *cmd, t_built_f built_f);
static int	ft_save_stdio_fileno(t_fd_io *fd_io);

int	ft_in_shell(t_msh *msh, t_exl *exl, t_cmd *cmd, t_built_f built_f)
{
	t_fd_io	s_origin_stdio_fd;
	int		err_code;

	++exl->cmd_idx;
	if (ft_save_stdio_fileno(&s_origin_stdio_fd) == -1)
		return (1);
	err_code = 0;
	// ft_default_redirections(exl) ????
	if (ft_default_redirections(exl) != 0 \
		|| ft_set_redirections(exl, cmd) != 0 \
		|| ft_apply_redirections(exl) != 0)
		err_code = 1;
	if (err_code == 0 && built_f != NULL)
		err_code = built_f(msh, cmd->args + 1);
	// how to protect dup2 in this situatin??
	dup2(s_origin_stdio_fd.fd_to_read, STDIN_FILENO);
	dup2(s_origin_stdio_fd.fd_to_write, STDOUT_FILENO);
	// ft_close_used_pipes(&exl->s_fd_io);
	ft_close_used_pipes(&s_origin_stdio_fd);
	// return 1 if dup2 fails??
	return (err_code);
}

static int	ft_save_stdio_fileno(t_fd_io *fd_io)
{
	fd_io->fd_to_read = dup(STDIN_FILENO);
	fd_io->fd_to_write = dup(STDOUT_FILENO);
	if (fd_io->fd_to_read == -1 || fd_io->fd_to_write == -1)
	{
		close(fd_io->fd_to_read);
		close(fd_io->fd_to_write);
		return (-1);
	}
	return (0);
}
