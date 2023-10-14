#include "heredoc.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int			ft_heredoc(t_cmd *cmd_list, t_exl *exl);
char		*ft_get_hd_content(char *del, int *line_num);
static int	ft_search_for_hd(t_cmd *cmd, t_hd *hd, int *line_num);
static bool	ft_end_of_hd(char *current_line, char *del, int line_num);
static char	*ft_update_hd_content(char *hd_content, char *current_line);

int	ft_heredoc(t_cmd *cmd_list, t_exl *exl)
{
	ssize_t	i;

	i = -1;
	while (++i < exl->n_cmd)
		if (ft_search_for_hd(cmd_list + i, &exl->hd, exl->line_num) == -1)
			return (-1);
	return (0);
}

char	*ft_get_hd_content(char *del, int *line_num)
{
	const int	first_line = *line_num;	
	char		*hd_content;
	char		*current_line;

	// add toogle of expansion following quotes rules in delimiteur
	hd_content = ft_calloc(1, sizeof(char));
	if (hd_content == NULL)
		return (NULL);
	current_line = readline(HD_PROMPT);
	while (ft_end_of_hd(current_line, del, first_line) == false)
	{
		hd_content = ft_update_hd_content(hd_content, current_line);
		if (hd_content == NULL)
			break ;
		(*line_num)++;
		current_line = readline(HD_PROMPT);
	}
	return (hd_content);
}

static int	ft_search_for_hd(t_cmd *cmd, t_hd *hd, int *line_num)
{
	t_redirect	*current_redir;
	ssize_t		j;

	j = -1;
	while (++j < cmd->n_redirect)
	{
		current_redir = cmd->redirect_arr + j;
		if (current_redir->e_iotype == HEREDOC \
			&& ft_update_hd_list(hd, current_redir->file, line_num) == -1)
		{
			// perror()
			return (-1);
		}
	}
	return (0);
}

static bool	ft_end_of_hd(char *current_line, char *del, int line_num)
{
	if (current_line == NULL || ft_strcmp(current_line, del) == 0)
	{
		if (current_line == NULL)
			printf("msh: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", line_num, del);
		else
			free(current_line);
		return (true);
	}
	return (false);
}

static char	*ft_update_hd_content(char *hd_content, char *current_line)
{
	char	*former_line;

	former_line = hd_content;
	hd_content = ft_join(3, former_line, current_line, "\n");
	ft_freef("%p%p", former_line, current_line);
	return (hd_content);
}
