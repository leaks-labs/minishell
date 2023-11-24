/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_hd_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:30:30 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 22:30:31 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "msh_signal.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

char	*ft_init_hd_content(char **hd_content);
char	*ft_retrieve_one_line(void);
bool	ft_end_of_hd(char *current_line, char *del, unsigned int line_num);
char	*ft_do_expansion(t_msh *msh, char *current_line, bool to_expand);
char	*ft_update_hd_content(char *hd_content, char *current_line);

char	*ft_init_hd_content(char **hd_content)
{
	*hd_content = ft_calloc(1, sizeof(char));
	return (*hd_content);
}

char	*ft_retrieve_one_line(void)
{
	char	*current_line;

	ft_set_signals(MSH_SIG_HEREDOC);
	current_line = readline(HD_PROMPT);
	ft_set_signals(MSH_SIG_IGN);
	if (g_signal_value > 0 && current_line != NULL)
		current_line = ft_freef("%p", current_line);
	return (current_line);
}

bool	ft_end_of_hd(char *current_line, char *del, unsigned int line_num)
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

char	*ft_do_expansion(t_msh *msh, char *current_line, bool to_expand)
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

char	*ft_update_hd_content(char *hd_content, char *current_line)
{
	char	*former_line;

	if (current_line == NULL)
		return (ft_freef("%p", hd_content));
	former_line = hd_content;
	hd_content = ft_join(3, former_line, current_line, "\n");
	ft_freef("%p%p", former_line, current_line);
	return (hd_content);
}
