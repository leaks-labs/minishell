/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:56 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/25 00:07:56 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"
#include <stdlib.h>

int			ft_mod_env2(t_list *env, const char *name, const char *val, int f);
int			ft_mod_env1(t_list *env, const char *arg, int f);
static int	ft_update_var(t_list *env, t_var *var, const char *arg, int f);
static int	ft_assign_value(t_var *var, const char *arg);
static int	ft_append_value(t_var *var, const char *arg);

int	ft_mod_env2(t_list *env, const char *name, const char *val, int f)
{
	char	*assignation;
	int		err_code;

	if (name == NULL)
		return (0);
	if (val == NULL && (f & ENV_APPEND) == ENV_APPEND)
		assignation = ft_join(2, name, "+=");
	else if (val == NULL && (f & ENV_ASSIGN) == ENV_ASSIGN)
		assignation = ft_join(2, name, "=");
	else if (val == NULL)
		assignation = ft_strdup(name);
	else if ((f & ENV_APPEND) == ENV_APPEND)
		assignation = ft_join(3, name, "+=", val);
	else
		assignation = ft_join(3, name, "=", val);
	if (assignation == NULL)
		return (-1);
	err_code = ft_mod_env1(env, assignation, f);
	free(assignation);
	return (err_code);
}

int	ft_mod_env1(t_list *env, const char *arg, int f)
{
	t_var	*var;

	if (ft_isappend(arg) == true)
		f |= ENV_APPEND;
	else if (ft_isassignation(arg) == true)
		f |= ENV_ASSIGN;
	var = ft_get_var(env, arg);
	if (var != NULL)
		return (ft_update_var(env, var, arg, f) == -1);
	else
		return (ft_add_var(env, arg, f) == -1);
}

static int	ft_update_var(t_list *env, t_var *var, const char *arg, int f)
{
	if ((f & ENV_APPEND) == ENV_APPEND && ft_append_value(var, arg) == -1)
		return (-1);
	else if ((f & ENV_ASSIGN) == ENV_ASSIGN && ft_assign_value(var, arg) == -1)
		return (-1);
	if ((f & ENV_EXP) == ENV_EXP)
	{
		env->n_exported += (var->exported == false);
		var->exported = true;
	}
	else if ((f & ENV_NOEXP) == ENV_NOEXP)
	{
		env->n_exported -= (var->exported == true);
		var->exported = false;
	}
	return (0);
}

static int	ft_assign_value(t_var *var, const char *arg)
{
	char	*value;

	value = ft_strdup(arg + ft_get_name_len(arg) + 1);
	if (value == NULL)
		return (-1);
	free(var->value);
	var->value = value;
	return (0);
}

static int	ft_append_value(t_var *var, const char *arg)
{
	char	*new_value;

	if (var->value == NULL)
		new_value = ft_strdup(arg + ft_get_name_len(arg) + 2);
	else
		new_value = ft_join(2, var->value, arg + ft_get_name_len(arg) + 2);
	if (new_value == NULL)
		return (-1);
	free(var->value);
	var->value = new_value;
	return (0);
}
