/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:39 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:53:40 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SIGNAL_H
# define MSH_SIGNAL_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal_value;

typedef enum msh_signals
{
	MSH_SIG_IGN,
	MSH_SIG_HEREDOC,
	MSH_SIG_EXT_CMD,
	MSH_SIG_REPROMPT
}			t_msh_signals;

/*	SET_SIGNALS	*/
void	ft_set_signals(t_msh_signals e_msh_signals);
/*	SIGHANDLERS	*/
void	ft_sighandler_heredoc(int sig);
void	ft_sighandler_reprompt(int sig);

#endif
