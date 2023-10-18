#ifndef MSH_SIGNALS_H
# define MSH_SIGNALS_H

#include <signal.h>

extern sig_atomic_t	g_interrupt_heredoc;

typedef enum msh_signals
{
	MSH_SIG_PARENT,
	MSH_SIG_HEREDOC,
	MSH_SIG_CHILD,
	MSH_SIG_REPROMPT
}			t_msh_signals;

void	ft_set_signals(t_msh_signals e_msh_signals);

#endif