#include "heredoc.h"
#include "redirections.h"
#include "utils.h"
#include <fcntl.h>
#include <sys/pipe.h>
#include <stdio.h>
#include <unistd.h>

int	ft_set_input(t_exl *exl, char *file);
int	ft_set_heredoc(t_exl *exl, char *file);
int	ft_set_output(t_exl *exl, char *file);
int	ft_set_append(t_exl *exl, char *file);

int	ft_set_input(t_exl *exl, char *file)
{
	(void)exl;
	if (exl->s_fd_io.fd_to_read != STDIN_FILENO)
		close(exl->s_fd_io.fd_to_read);
	exl->s_fd_io.fd_to_read = open(file, O_RDONLY);
	if (exl->s_fd_io.fd_to_read == -1)
	{
		ft_putstr_fd(MSH_ERROR_PROMPT, STDERR_FILENO);
		perror(file);
	}
	return (exl->s_fd_io.fd_to_read);
}

int	ft_set_heredoc(t_exl *exl, char *file)
{
	char	*content;

	(void)file;
	content = exl->hd.hd_list->hd_content;
	if (exl->s_fd_io.fd_to_read != STDIN_FILENO)
		close(exl->s_fd_io.fd_to_read);
	if (ft_strlen(content) < PIPE_SIZE)
		exl->s_fd_io.fd_to_read = ft_fill_tmp_pipe(content);
	else
		exl->s_fd_io.fd_to_read = ft_fill_tmp_file(content);
	exl->hd.hd_list = ft_delete_front_hd_node(exl->hd.hd_list);
	return (exl->s_fd_io.fd_to_read);
}

int	ft_set_output(t_exl *exl, char *file)
{
	(void)exl;
	if (exl->s_fd_io.fd_to_write != STDOUT_FILENO)
		close(exl->s_fd_io.fd_to_write);
	// verfy the 0644, to be the good rights
	exl->s_fd_io.fd_to_write = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (exl->s_fd_io.fd_to_write == -1)
	{
		ft_putstr_fd(MSH_ERROR_PROMPT, STDERR_FILENO);
		perror(file);
	}
	return (exl->s_fd_io.fd_to_write);
}

int	ft_set_append(t_exl *exl, char *file)
{
	(void)exl;
	if (exl->s_fd_io.fd_to_write != STDOUT_FILENO)
		close(exl->s_fd_io.fd_to_write);
	// verfy the 0644, to be the good rights
	exl->s_fd_io.fd_to_write = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (exl->s_fd_io.fd_to_write == -1)
	{
		ft_putstr_fd(MSH_ERROR_PROMPT, STDERR_FILENO);
		perror(file);
	}
	return (exl->s_fd_io.fd_to_write);
}
