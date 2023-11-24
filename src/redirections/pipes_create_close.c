/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_create_close.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:34 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:56:35 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include <unistd.h>

int		ft_createpipe(int *pp);
void	ft_close_used_pipes(t_fd_io *fd_io);

int	ft_createpipe(int *pp)
{
	if (pipe(pp) == -1)
	{
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
