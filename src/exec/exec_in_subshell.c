#include "exec.h"
#include "msh_signal.h"
#include "path.h"
#include "redirections.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int				ft_exec_in_subshell(t_exl *exl, t_pipeline *pipeline);
static pid_t	ft_child_process(t_exl *exl, t_cmd *cmd);
static int		ft_launch_extern_cmd(t_exl *exl, char **args);
static char		**ft_lst_to_env(t_list *env);
static char		*ft_one_var_to_str(t_var *var);
static int		ft_get_err_code(char *cmd);
static int		ft_wait(pid_t last_pid);

int	ft_exec_in_subshell(t_exl *exl, t_pipeline *pipeline)
{
	t_cmd	*current_cmd;
	pid_t	last_pid;

	if (exl->path == NULL)
		exl->path = ft_get_path(exl->env);
	while (++exl->cmd_idx < exl->n_cmd)
	{
		last_pid = -1;
		current_cmd = pipeline->cmd_list + exl->cmd_idx;
		if (ft_default_redirections(exl) == 0)
			last_pid = ft_child_process(exl, current_cmd);
		ft_close_used_pipes(&exl->s_fd_io);
	}
	return (ft_wait(last_pid));
}

static pid_t	ft_child_process(t_exl *exl, t_cmd *cmd)
{
	const pid_t		pid = fork();
	t_built_func	built_func;
	int				err_code;

	// if (pid == -1)
	// 	perror("fork error");
	if (pid != 0)
		return (pid);
	err_code = 0;
	if (ft_set_redirections(exl, cmd) != 0 || ft_apply_redirections(exl) != 0)
		err_code = 1;
	if (err_code == 0 && cmd->args != NULL)
	{
		built_func = ft_get_builtin(cmd->args[0]);
		if (built_func != NULL)
			err_code = built_func(exl->env, cmd->args + 1);
		else
			err_code = ft_launch_extern_cmd(exl, cmd->args);
	}
	// else if (err_code == 0 && cmd->args != NULL)
	// 	err_code = ft_launch_extern_cmd(exl, cmd->args);
	ft_close_used_pipes(&exl->s_fd_io);
	// free other struct extern to exl (like pipeline, msh, history, line...) ??
	exit(err_code);
}

static int	ft_launch_extern_cmd(t_exl *exl, char **args)
{
	char	*cmd_path;
	char	**export_env;

	cmd_path = ft_get_cmd_path(exl->path, args[0]);
	if (cmd_path != NULL)
	{
		// is it in the right place? Better to be earlier?
		export_env = ft_lst_to_env(exl->env);
		ft_set_signals(MSH_SIG_EXT_CMD);
		execve(cmd_path, args, export_env);
		ft_set_signals(MSH_SIG_IGN);
		free(export_env);
	}
	free(cmd_path);
	return (ft_get_err_code(args[0]));
}

static char	**ft_lst_to_env(t_list *env)
{
	char		**export_env;
	t_list_node	*node;
	t_var		*var;
	size_t		i;

	export_env = ft_calloc(env->n_exported + 1, sizeof(char *));
	if (export_env == NULL)
		return (NULL);
	node = env->list_node;
	i = 0;
	while (node != NULL)
	{
		var = (t_var *)node->content;
		if (var->exported == true && var->value != NULL)
		{
			export_env[i] = ft_one_var_to_str((t_var *)node->content);
			if (export_env[i] == NULL)
				return (ft_freef("%P", export_env));
			++i;
		}
		node = node->next;
	}
	return (export_env);
}

static char	*ft_one_var_to_str(t_var *var)
{
	return (ft_join(3, var->name, "=", var->value));
}

static int	ft_get_err_code(char *cmd)
{
	if (errno == ENOENT || errno == ENAMETOOLONG)
	{
		ft_putstr_fd(MSH_ERROR_PROMPT, STDERR_FILENO);
		if (ft_isapath(cmd) == true)
			perror(cmd);
		else
		{
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}
		return (COMMAND_NOT_FOUND);
	}
	else if (errno == EISDIR || errno == ENOTDIR || errno == ENOEXEC)
	{
		ft_putstr_fd(MSH_ERROR_PROMPT, STDERR_FILENO);
		perror(cmd);
		return (COMMAND_NOT_EXECUTABLE);
	}
	else
		return (EXIT_FAILURE);
	// need to print error (perror()) for other error types?
}

static int	ft_wait(pid_t last_pid)
{
	int	wstatus;
	int	exit_status;

	if (last_pid != -1)
	{
		waitpid(last_pid, &wstatus, 0);
		if (WIFSIGNALED(wstatus))
		{
			exit_status = 128 + WTERMSIG(wstatus);
			if (exit_status == 128 + SIGQUIT)
				printf("Quit: %d", SIGQUIT);
			printf("\n");
		}
		else if (WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
		else
			exit_status = 1;
	}
	else
		exit_status = 1;
	while (wait(NULL) != -1 || errno != ECHILD)
		;
	return (exit_status);
}
