/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:48 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:56:49 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_signal.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <readline/readline.h>

void	ft_sighandler_heredoc(int sig);
void	ft_sighandler_reprompt(int sig);

void	ft_sighandler_heredoc(int sig)
{
	struct termios	orig_termios;
	struct termios	new_termios;

	g_signal_value = sig;
	tcgetattr(STDIN_FILENO, &orig_termios);
	tcgetattr(STDIN_FILENO, &new_termios);
	new_termios.c_lflag &= (tcflag_t)(~(ICANON | ECHO));
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void	ft_sighandler_reprompt(int sig)
{
	(void)sig;
	if (g_signal_value != EOF)
		write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
