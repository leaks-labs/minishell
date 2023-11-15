#include "exec.h"
#include "env.h"
#include "heredoc.h"
#include "init.h"
#include "msh_signal.h"
#include "utils.h"

uint8_t				ft_exec_line(t_msh *msh, t_pl *pl);
static int			ft_init_exl(t_exl *exl, t_msh *msh, t_pl *pl);
static int			ft_exec_cmd(t_msh *msh, t_exl *exl, t_pl *pl);
static void			ft_update_last_arg(t_list *env, t_pl *pl);
static const char	*ft_get_last_arg(const char **args);

// #include "utils.h"
// #include <unistd.h>
uint8_t	ft_exec_line(t_msh *msh, t_pl *pl)
{
	t_exl	s_exl;
	int		exit_code;

	// pl->cmd_list = ft_calloc(1, sizeof(t_cmd));
	// pl->n_cmd = 1;
	// pl->cmd_list->n_redirect = 0;
	// pl->cmd_list->args = ft_split("ls", ' ');
	// pl->cmd_list->redirect_arr = ft_calloc(1, sizeof(t_redirect));
	// pl->cmd_list->redirect_arr->file = ft_strdup("\" \"");
	// pl->cmd_list->redirect_arr->e_iotype = HEREDOC;

	if (ft_init_exl(&s_exl, msh, pl) == -1)
	{
		if (g_signal_value > 0)
			return ((uint8_t)(128 + g_signal_value));
		return (1);
	}
	exit_code = ft_exec_cmd(msh, &s_exl, pl);
	ft_update_last_arg(&msh->env, pl);
	ft_free_cmd_list(pl);
	return ((uint8_t)exit_code);
}

static int	ft_init_exl(t_exl *exl, t_msh *msh, t_pl *pl)
{
	exl->env = &msh->env;
	exl->path = msh->path;
	exl->line_num = &msh->line_num;
	exl->cmd_idx = -1;
	exl->n_cmd = pl->n_cmd;
	return (ft_heredoc(pl->cmd_list, exl));
}

static int	ft_exec_cmd(t_msh *msh, t_exl *exl, t_pl *pl)
{
	t_built_f		built_f;
	t_in_shell_pmt	pmt;

	built_f = NULL;
	pmt.msh = msh;
	pmt.pl = pl;
	pmt.exl = exl;
	if (pl->n_cmd == 1)
	{
		if (pl->cmd_list->args != NULL)
			built_f = ft_get_builtin(*pl->cmd_list->args);
		if (pl->cmd_list->args == NULL || built_f != NULL)
			return (ft_in_shell(&pmt, pl->cmd_list, built_f));
	}
	return (ft_in_subshell(msh, exl, pl));
}

static void	ft_update_last_arg(t_list *env, t_pl *pl)
{
	const char	*last_arg;

	if (pl->n_cmd > 1)
		return ;
	last_arg = ft_get_last_arg((const char **)pl->cmd_list->args);
	ft_mod_env2(env, "_", last_arg, ENV_ASSIGN | ENV_NOEXP);
	// check error mod_env2 or not?
}

static const char	*ft_get_last_arg(const char **args)
{
	if (args == NULL)
		return (NULL);
	return (args[ft_dptrlen(args) - 1]);
}
