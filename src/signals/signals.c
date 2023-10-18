#include "msh_signals.h"
#include <sys/ioctl.h>
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <readline/readline.h>

void 		rl_replace_line(const char *text, int clear_undo);

void		ft_set_signals(t_msh_signals e_msh_signals);
static void	ft_set_sighandler_parent(void);
static void	ft_set_sighandler_heredoc(void);
static void	ft_sighandler_heredoc(int sig);
static void	ft_set_sighandler_child(void);
static void	ft_set_sighandler_reprompt(void);
static void	ft_sighandler_reprompt(int sig);

sig_atomic_t	g_interrupt_heredoc;

void	ft_set_signals(t_msh_signals e_msh_signals)
{
	void	(*f[4])(void);

	(f)[MSH_SIG_PARENT] = &ft_set_sighandler_parent;
	(f)[MSH_SIG_HEREDOC] = &ft_set_sighandler_heredoc;
	(f)[MSH_SIG_CHILD] = &ft_set_sighandler_child;
	(f)[MSH_SIG_REPROMPT] = &ft_set_sighandler_reprompt;
	(f)[e_msh_signals]();
}

static void	ft_set_sighandler_parent(void)
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
	g_interrupt_heredoc = false;
}

static void	ft_sighandler_heredoc(int sig)
{
	(void)sig;
	g_interrupt_heredoc = true;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

static void	ft_set_sighandler_child(void)
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

static void	ft_sighandler_reprompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
