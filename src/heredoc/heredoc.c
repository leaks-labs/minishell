#include "heredoc.h"
#include <stdlib.h>

int			ft_heredoc(t_cmd *cmd_list, t_exl *exl);
static int	ft_search_for_hd(t_cmd *cmd, unsigned int *line_num);
static int	ft_update_redirect(t_redirect *redir, unsigned int *line_num);

int	ft_heredoc(t_cmd *cmd_list, t_exl *exl)
{
	size_t	i;

	i = 0;
	while (i < exl->n_cmd)
		if (ft_search_for_hd(cmd_list + i++, exl->line_num) == -1)
			return (-1);
	return (0);
}

static int	ft_search_for_hd(t_cmd *cmd, unsigned int *line_num)
{
	t_redirect	*current_redir;
	size_t		i;

	i = 0;
	while (i < cmd->n_redirect)
	{
		current_redir = cmd->redirect_arr + i++;
		if (current_redir->e_iotype == IO_HEREDOC \
			&& ft_update_redirect(current_redir, line_num) == -1)
		{
			// perror()
			return (-1);
		}
	}
	return (0);
}

static int	ft_update_redirect(t_redirect *redir, unsigned int *line_num)
{
	char	*hd_content;

	hd_content = ft_get_hd_content(redir->file, line_num);
	if (hd_content == NULL)
		return (-1);
	free(redir->file);
	redir->file = hd_content;
	return (0);
}
