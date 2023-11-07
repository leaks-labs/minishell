#include "exec.h"
#include "heredoc.h"
#include "msh_signal.h"

uint8_t		ft_exec_line(t_msh *msh, t_pipeline *pipeline);
static int	ft_init_exl(t_exl *exl, t_msh *msh, t_pipeline *pipeline);
static int	ft_exec_cmd(t_exl *exl, t_pipeline *pipeline);

uint8_t	ft_exec_line(t_msh *msh, t_pipeline *pipeline)
{
	t_exl	s_exl;
	int		exit_code;

	// pipeline->cmd_list = ft_calloc(1, sizeof(t_cmd));
	// pipeline->n_cmd = 1;
	// pipeline->cmd_list->n_redirect = 1;
	// pipeline->cmd_list->args = ft_split("ls", ' ');
	// pipeline->cmd_list->redirect_arr = ft_calloc(1, sizeof(t_redirect));
	// pipeline->cmd_list->redirect_arr->file = ft_strdup("testfile");
	// pipeline->cmd_list->redirect_arr->e_iotype = OUTPUT;

	if (ft_init_exl(&s_exl, msh, pipeline) == -1)
	{
		if (g_signal_value > 0)
			return ((uint8_t)(128 + g_signal_value));
		return (1);
	}
	exit_code = ft_exec_cmd(&s_exl, pipeline);
	// free other struct extern to exl (like pipeline) ??
	return ((uint8_t)exit_code);
}

static int	ft_init_exl(t_exl *exl, t_msh *msh, t_pipeline *pipeline)
{
	exl->env = &msh->env;
	exl->path = msh->path;
	exl->line_num = &msh->line_num;
	exl->cmd_idx = -1;
	exl->n_cmd = pipeline->n_cmd;
	return (ft_heredoc(pipeline->cmd_list, exl));
}

static int	ft_exec_cmd(t_exl *exl, t_pipeline *pipeline)
{
	t_built_func	built_func;

	if (pipeline->n_cmd == 1)
	{
		built_func = ft_get_builtin(*pipeline->cmd_list->args);
		if (pipeline->cmd_list->args == NULL || built_func != NULL)
			return (ft_exec_in_shell(built_func, exl, pipeline->cmd_list));
	}
	return (ft_exec_in_subshell(exl, pipeline));
}
