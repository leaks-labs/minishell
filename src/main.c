/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:21:55 by shinfray          #+#    #+#             */
/*   Updated: 2023/08/18 15:56:01 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	s_ms;
	char	*text;

	(void)argc;
	(void)argv;
	(void)envp;
	s_ms.env = ft_dptrcpy(envp);
	text = readline(PROMPT);
	while (text != NULL)
	{
		if (*text != '\0')
			add_history(text);
		if (*text != '\0')
			printf("%s\n", text);
		free(text);
		text = readline(PROMPT);
	}
	free(text);
	free(s_ms.env);
	rl_clear_history();
	return (0);
}