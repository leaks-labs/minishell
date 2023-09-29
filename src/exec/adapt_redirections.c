#include "exec.h"

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
	int		pipe[2];

	(void)file;
	content = exl->hd.hd_list->hd_content;
	if (exl->s_fd_io.fd_to_read != STDIN_FILENO)
		close(exl->s_fd_io.fd_to_read);
	if (ft_createpipe(pipe) == 0)
	{
		write(pipe[1], content, ft_strlen(content));
		close(pipe[1]);
	}
	exl->s_fd_io.fd_to_read = pipe[0];
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
