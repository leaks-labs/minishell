/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:30:22 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 22:30:23 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "msh_signal.h"
#include "utils.h"
#include <stdlib.h>

int			ft_heredoc(t_msh *msh, t_cmd *cmd_list, t_exl *exl);
static int	ft_search_for_hd(t_msh *msh, t_cmd *cmd, unsigned int *line_n);
static int	ft_set_content(t_msh *msh, t_redirect *redir, unsigned int *line_n);
static char	*ft_get_hd_content(t_msh *msh, char *del, unsigned int *line_num);

int	ft_heredoc(t_msh *msh, t_cmd *cmd_list, t_exl *exl)
{
	size_t	i;

	i = 0;
	while (i < exl->n_cmd)
		if (ft_search_for_hd(msh, cmd_list + i++, exl->line_num) == -1)
			return (-1);
	return (0);
}

static int	ft_search_for_hd(t_msh *msh, t_cmd *cmd, unsigned int *line_n)
{
	t_redirect	*current_redir;
	size_t		i;

	i = 0;
	while (i < cmd->n_redirect)
	{
		current_redir = cmd->redirect_arr + i++;
		if (current_redir->e_iotype == IO_HEREDOC \
			&& ft_set_content(msh, current_redir, line_n) == -1)
			return (-1);
	}
	return (0);
}

static int	ft_set_content(t_msh *msh, t_redirect *redir, unsigned int *line_n)
{
	char	*hd_content;

	hd_content = ft_get_hd_content(msh, redir->file, line_n);
	if (hd_content == NULL)
		return (-1);
	free(redir->file);
	redir->file = hd_content;
	return (0);
}

static char	*ft_get_hd_content(t_msh *msh, char *del, unsigned int *line_num)
{
	const bool			to_expand = (ft_strchr(del, '\"') == NULL \
									&& ft_strchr(del, '\'') == NULL);
	const unsigned int	first_line_num = *line_num;	
	char				*hd_content;
	char				*current_line;

	if (to_expand == false)
		ft_rm_quotes(del);
	if (ft_init_hd_content(&hd_content) == NULL)
		return (NULL);
	current_line = ft_retrieve_one_line();
	if (g_signal_value > 0)
		return (ft_freef("%p", hd_content));
	while (ft_end_of_hd(current_line, del, first_line_num) == false)
	{
		current_line = ft_do_expansion(msh, current_line, to_expand);
		hd_content = ft_update_hd_content(hd_content, current_line);
		if (hd_content == NULL)
			break ;
		(*line_num)++;
		current_line = ft_retrieve_one_line();
		if (g_signal_value > 0)
			return (ft_freef("%p", hd_content));
	}
	return (hd_content);
}
