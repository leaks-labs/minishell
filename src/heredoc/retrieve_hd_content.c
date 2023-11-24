/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_hd_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:55:36 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 19:18:14 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "msh_signal.h"
#include "parse.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

char		*ft_get_hd_content(t_msh *msh, char *del, unsigned int *line_num);
static char	*ft_retrieve_one_line(void);
static bool	ft_end_of_hd(char *current_line, char *del, unsigned int line_num);
static char	*ft_do_expansion(t_msh *msh, char *current_line, bool to_expand);
static char	*ft_update_hd_content(char *hd_content, char *current_line);

char	*ft_get_hd_content(t_msh *msh, char *del, unsigned int *line_num)
{
	const bool			to_expand = (ft_strchr(del, '\"') == NULL \
									&& ft_strchr(del, '\'') == NULL);
	const unsigned int	first_line_num = *line_num;	
	char				*hd_content;
	char				*current_line;

	if (to_expand == false)
		ft_rm_quotes(del);
	hd_content = ft_calloc(1, sizeof(char));
	if (hd_content == NULL)
		return (NULL);
	current_line = ft_retrieve_one_line();
	if (g_signal_value > 0)
		return (ft_freef("%p", hd_content));
	while (ft_end_of_hd(current_line, del, first_line_num) == false)
	{
		current_line = ft_do_expansion(msh, current_line, to_expand);
		// protect current_line;
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

static char	*ft_retrieve_one_line(void)
{
	char	*current_line;

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
			printf("msh: warning: here-document at line %d ", line_num);
			printf("delimited by end-of-file (wanted `%s')\n", del);
			g_signal_value = EOF;
		}
		else
			free(current_line);
		return (true);
	}
	return (false);
}

static char	*ft_do_expansion(t_msh *msh, char *current_line, bool to_expand)
{
	char	*tmp;

	if (current_line != NULL && to_expand == true)
	{
		tmp = current_line;
		current_line = ft_expansion_monitor(msh, current_line, false);
		free(tmp);
	}
	return (current_line);
}

static char	*ft_update_hd_content(char *hd_content, char *current_line)
{
	char	*former_line;

	former_line = hd_content;
	hd_content = ft_join(3, former_line, current_line, "\n");
	ft_freef("%p%p", former_line, current_line);
	return (hd_content);
}
