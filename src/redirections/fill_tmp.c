/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:32 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 15:05:53 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include "utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int			ft_fill_tmp_pipe(const char *content);
int			ft_fill_tmp_file(const char *content);
static char	*ft_get_tmp_filename(void);

int	ft_fill_tmp_pipe(const char *content)
{
	int	pipe[2];

	if (ft_createpipe(pipe) == 0)
	{
		write(pipe[1], content, ft_strlen(content));
		close(pipe[1]);
	}
	return (pipe[0]);
}

int	ft_fill_tmp_file(const char *content)
{
	char	*filename;
	int		fd_origin;
	int		fd;

	filename = ft_get_tmp_filename();
	if (filename == NULL)
		return (-1);
	fd_origin = open(filename, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd_origin == -1)
	{
		free(filename);
		return (-1);
	}
	fd = dup(fd_origin);
	if (fd != -1)
	{
		write(fd, content, ft_strlen(content));
		close(fd);
		fd = open(filename, O_RDONLY);
	}
	close(fd_origin);
	unlink(filename);
	free(filename);
	return (fd);
}

static char	*ft_get_tmp_filename(void)
{
	static uintmax_t	ext;
	char				ext_buf[MAX_LEN_NUM + 1];

	ft_uimaxtostr(ext_buf, MAX_LEN_NUM + 1, ext++);
	return (ft_join(2, TMP_FILE_BASE_NAME, ext_buf));
}
