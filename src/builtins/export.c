#include "builtin.h"
#include "env.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

int			ft_export(t_list *env, char **args);
static int	ft_print_export(t_list *env);
static int	ft_export_args_iter(t_list *env, char **args);
static int	ft_mod_env(t_list *env, char *arg, int flags);
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
	t_var		*var;
	size_t		index;

	index = 0;
	while (index < env->n_var)
	{
		var = ft_get_var_per_index(env, index++);
		if (var != NULL && var->exported == true)
		{
			if (var->value != NULL)
				printf("declare -x %s=\"%s\"\n", var->name, var->value);
			else
				printf("declare -x %s\n", var->name);
		}
	}
	return (0);
}

static int	ft_export_args_iter(t_list *env, char **args)
{
	int		err_code;

	err_code = 0;
	while (*args != NULL)
	{
		if (ft_isvalidname(*args) == true)
		{
			if (ft_mod_env(env, *args, ENV_EXP) == -1)
				err_code = 1;
		}
		else
		{
			ft_print_error_export(*args);
			err_code = 1;
		}
		++args;
	}
	return (err_code);
}

static int	ft_mod_env(t_list *env, char *arg, int flags)
{
	t_var	*var;

	if (ft_isassignation(arg) == true)
		flags |= ENV_ASSIGN;
	var = ft_get_var(env, arg);
	if (var != NULL)
		return (ft_update_var(env, var, arg, flags) == -1);
	else
		return (ft_add_var(env, arg, flags) == -1);
}

static void	ft_print_error_export(char *arg)
{
	ft_putstr_fd(MSH_ERROR_PROMPT, STDERR_FILENO);
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}
