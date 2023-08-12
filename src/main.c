/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:21:55 by shinfray          #+#    #+#             */
/*   Updated: 2023/08/12 16:40:38 by shinfray         ###   ########.fr       */
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
    for (int i = 0; s_ms.env[i]; ++i) {
        printf("->%s\n", s_ms.env[i]);
    }

    printf("-->%s\n", ft_getenv("PATH", s_ms.env));
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
	rl_clear_history();
	return (0);
}