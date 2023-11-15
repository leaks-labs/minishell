#include "heredoc.h"
#include "msh_signal.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

char		*ft_get_hd_content(char *del, unsigned int *line_num);
static void	ft_rm_quotes(char *del);
static char	*ft_retrieve_one_line(bool to_expand);
static bool	ft_end_of_hd(char *current_line, char *del, unsigned int line_num);
static char	*ft_update_hd_content(char *hd_content, char *current_line);

char	*ft_get_hd_content(char *del, unsigned int *line_num)
{
	const unsigned int	first_line_num = *line_num;	
	char				*hd_content;
	char				*current_line;
	bool				to_expand;

	to_expand = (ft_strchr(del, '\"') == NULL && ft_strchr(del, '\'') == NULL);
	if (to_expand == false)
		ft_rm_quotes(del);
	hd_content = ft_calloc(1, sizeof(char));
	if (hd_content == NULL)
		return (NULL);
	current_line = ft_retrieve_one_line(to_expand);
	if (g_signal_value > 0)
		return (ft_freef("%p", hd_content));
	while (ft_end_of_hd(current_line, del, first_line_num) == false)
	{
		hd_content = ft_update_hd_content(hd_content, current_line);
		if (hd_content == NULL)
			break ;
		(*line_num)++;
		current_line = ft_retrieve_one_line(to_expand);
		if (g_signal_value > 0)
			return (ft_freef("%p", hd_content));
	}
	return (hd_content);
}

static void	ft_rm_quotes(char *del)
{
	char	to_trim;
	size_t	i;
	size_t	j;

	to_trim = '\0';
	i = 0;
	j = i;
	while (del[i] != '\0')
	{
		if (to_trim == '\0' && (del[i] == '\"' || del[i] == '\''))
			to_trim = del[i];
		else if (to_trim != '\0' && del[i] == to_trim)
			to_trim = '\0';
		else
			del[j++] = del[i];
		++i;
	}
	del[j] = '\0';
}

static char	*ft_retrieve_one_line(bool to_expand)
{
	char	*current_line;

	(void)to_expand;
	ft_set_signals(MSH_SIG_HEREDOC);
	current_line = readline(HD_PROMPT);
	ft_set_signals(MSH_SIG_IGN);
	if (g_signal_value > 0 && current_line != NULL)
		current_line = ft_freef("%p", current_line);
	return (current_line);
}

static bool	ft_end_of_hd(char *current_line, char *del, unsigned int line_num)
{
	if (current_line == NULL || ft_strcmp(current_line, del) == 0)
	{
		if (current_line == NULL)
		{
			printf("msh: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", line_num, del);
			g_signal_value = EOF;
		}
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
