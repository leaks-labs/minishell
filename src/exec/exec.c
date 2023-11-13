#include "exec.h"
#include "heredoc.h"
#include "msh_signal.h"

uint8_t		ft_exec_line(t_msh *msh, t_pipeline *pl);
static int	ft_init_exl(t_exl *exl, t_msh *msh, t_pipeline *pl);
static int	ft_exec_cmd(t_msh *msh, t_exl *exl, t_pipeline *pl);

// #include "utils.h"
// #include <unistd.h>
uint8_t	ft_exec_line(t_msh *msh, t_pipeline *pl)
{
	t_exl	s_exl;
	int		exit_code;

	// pl->cmd_list = ft_calloc(1, sizeof(t_cmd));
	// pl->n_cmd = 1;
	// pl->cmd_list->n_redirect = 0;
	// pl->cmd_list->args = ft_split("cd src", ' ');
	// pl->cmd_list->redirect_arr = ft_calloc(1, sizeof(t_redirect));
	// pl->cmd_list->redirect_arr->file = ft_strdup("testfile");
	// pl->cmd_list->redirect_arr->e_iotype = OUTPUT;

	if (ft_init_exl(&s_exl, msh, pl) == -1)
	{
		if (g_signal_value > 0)
			return ((uint8_t)(128 + g_signal_value));
		return (1);
	}
	exit_code = ft_exec_cmd(msh, &s_exl, pl);
	// free other struct extern to exl (like pipeline) ??
	return ((uint8_t)exit_code);
}

static int	ft_init_exl(t_exl *exl, t_msh *msh, t_pipeline *pl)
{
	exl->env = &msh->env;
	exl->path = msh->path;
	exl->line_num = &msh->line_num;
	exl->cmd_idx = -1;
	exl->n_cmd = pl->n_cmd;
	return (ft_heredoc(pl->cmd_list, exl));
}

static int	ft_exec_cmd(t_msh *msh, t_exl *exl, t_pipeline *pl)
{
	t_built_f	built_f;

	if (pl->n_cmd == 1)
	{
		built_f = ft_get_builtin(*pl->cmd_list->args);
		if (pl->cmd_list->args == NULL || built_f != NULL)
			return (ft_in_shell(msh, exl, pl->cmd_list, built_f));
	}
	return (ft_in_subshell(msh, exl, pl));
}
