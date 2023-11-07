#include "builtin.h"
#include "env.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

int			ft_export(t_list *env, char **args);
static int	ft_print_export(t_list *env);
static int	ft_export_args_iter(t_list *env, char **args);
static void	ft_print_error_export(char *arg);

int	ft_export(t_list *env, char **args)
{
	int		err_code;

	if (*args == NULL)
		err_code = ft_print_export(env);
	else
		err_code = ft_export_args_iter(env, args);
	return (err_code);
}

static int	ft_print_export(t_list *env)
{
	t_list_node	*node;
	t_var		*var;

	node = env->list_node;
	while (node != NULL)
	{
		var = (t_var *)node->content;
		if (var->exported == true)
			printf("declare -x %s", var->name);
		if (var->value != NULL)
			printf("=\"%s\"", var->value);
		printf("\n");
		node = node->next;
	}
	return (0);
}

static int	ft_export_args_iter(t_list *env, char **args)
{
	int		err_code;
	t_var	*var;
	int		flags;

	err_code = 0;
	while (*args != NULL)
	{
		if (ft_isvalidname(*args) == false)
		{
			ft_print_error_export(*args++);
			err_code = 1;
			continue ;
		}
		flags = ENV_EXP;
		if (ft_isassignation(*args) == true)
			flags |= ENV_ASSIGN;
		var = ft_get_var(env, *args);
		if (var != NULL)
		{
			if (ft_update_var(env, var, *args, flags) == -1)
				err_code = 1;
		}
		else if (ft_add_var(env, *args, flags) == -1)
			err_code = 1;
		++args;
	}
	return (err_code);
}

static void	ft_print_error_export(char *arg)
{
	ft_putstr_fd(MSH_ERROR_PROMPT, STDERR_FILENO);
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}
