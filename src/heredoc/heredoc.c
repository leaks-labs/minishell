#include "heredoc.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int			ft_heredoc(t_cmd *cmd_list, t_exl *exl);
static int	ft_update_hd_list(t_hd *hd, char *file);
static char	*ft_get_hd_content(char *del);
static char	*ft_add_nl(char *line);

int	ft_heredoc(t_cmd *cmd_list, t_exl *exl)
{
	t_redirect	*current_redir;
	ssize_t		i;
	ssize_t		j;

	exl->hd.hd_list = NULL;
	i = -1;
	while (++i < exl->n_cmd)
	{
		j = -1;
		while (++j < (cmd_list + i)->n_redirect)
		{
			current_redir = cmd_list[i].redirect_arr + j;
			if (current_redir->e_iotype == HEREDOC)
			{
				if (ft_update_hd_list(&exl->hd, current_redir->file) == -1)
				{
					// perror()
					return (-1);
				}
			}
		}
	}
	return (0);
}

static int	ft_update_hd_list(t_hd *hd, char *file)
{
	t_hd_node	*new_hd_node;
	char		*hd_content;

	hd_content = ft_get_hd_content(file);
	if (hd_content == NULL)
	{
		ft_free_hd_list(hd);
		return (-1);
	}
	new_hd_node = ft_calloc(1, sizeof(t_hd_node));
	if (new_hd_node == NULL)
	{
		free(hd_content);
		ft_free_hd_list(hd);
		return (-1);
	}
	new_hd_node->hd_content = hd_content;
	if (hd->hd_list == NULL)
		hd->hd_list = new_hd_node;
	else
		hd->last_node->next = new_hd_node;
	hd->last_node = new_hd_node;
	return (0);
}

static char	*ft_get_hd_content(char *del)
{
	char	*hd_content;
	char	*former_line;
	char	*current_line;

	// add toogle of expansion following quotes rules in delimiteur
	hd_content = NULL;
	// dont forget to count line and 
	//add error when stopping hd by other than delimiter
	current_line = readline(HD_PROMPT);
	if (current_line == NULL || ft_strcmp(current_line, del) == 0)
		return (ft_calloc(1, sizeof(char)));
	while (current_line != NULL && ft_strcmp(current_line, del) != 0)
	{
		if (current_line != NULL)
			current_line = ft_add_nl(current_line);
		former_line = hd_content;
		if (hd_content != NULL)
			hd_content = ft_join(2, former_line, current_line);
		else
			hd_content = ft_strdup(current_line);
		ft_freef("%p%p", former_line, current_line);
		if (hd_content == NULL)
			break ;
		current_line = readline(HD_PROMPT);
	}
	free(current_line);
	return (hd_content);
}

static char	*ft_add_nl(char *line)
{
	char	*line_w_nl;

	line_w_nl = ft_join(2, line, "\n");
	free(line);
	return (line_w_nl);
}
