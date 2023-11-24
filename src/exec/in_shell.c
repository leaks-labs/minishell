/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:14 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 15:09:20 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "redirections.h"
#include <unistd.h>

int			ft_in_shell(t_in_shell_pmt *pmt, t_cmd *cmd, t_built_f built_f);
static int	ft_save_stdio_fileno(t_fd_io *fd_io);

int	ft_in_shell(t_in_shell_pmt *pmt, t_cmd *cmd, t_built_f built_f)
{
	t_exl	*exl;
	t_fd_io	s_origin_stdio_fd;
	int		err_code;

	exl = pmt->exl;
	if (ft_save_stdio_fileno(&s_origin_stdio_fd) == -1)
		return (1);
	err_code = 0;
	if (ft_default_redirections(exl) != 0 \
		|| ft_set_redirections(exl, cmd) != 0 \
		|| ft_apply_redirections(exl) != 0)
		err_code = 1;
	if (err_code == 0 && built_f != NULL)
		err_code = built_f(pmt->msh, pmt->pl, cmd->args + 1);
	dup2(s_origin_stdio_fd.fd_to_read, STDIN_FILENO);
	dup2(s_origin_stdio_fd.fd_to_write, STDOUT_FILENO);
	ft_close_used_pipes(&s_origin_stdio_fd);
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
