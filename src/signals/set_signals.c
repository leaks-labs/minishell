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
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	ft_set_sighandler_reprompt(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_sighandler_reprompt;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
