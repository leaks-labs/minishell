/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:45 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 16:04:04 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_signal.h"
#include <stddef.h>

void		rl_replace_line(const char *text, int clear_undo);
void		ft_set_signals(t_msh_signals e_msh_signals);
static void	ft_set_sighandler_ign(void);
static void	ft_set_sighandler_heredoc(void);
static void	ft_set_sighandler_ext_cmd(void);
static void	ft_set_sighandler_reprompt(void);

void	ft_set_signals(t_msh_signals e_msh_signals)
{
	void	(*f[4])(void);

	(f)[MSH_SIG_IGN] = &ft_set_sighandler_ign;
	(f)[MSH_SIG_HEREDOC] = &ft_set_sighandler_heredoc;
	(f)[MSH_SIG_EXT_CMD] = &ft_set_sighandler_ext_cmd;
	(f)[MSH_SIG_REPROMPT] = &ft_set_sighandler_reprompt;
	(f)[e_msh_signals]();
}

static void	ft_set_sighandler_ign(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	ft_set_sighandler_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_sighandler_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	ft_set_sighandler_ext_cmd(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	ft_set_sighandler_reprompt(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_sighandler_reprompt;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
