#include "env.h"
#include "utils.h"
#include "stdlib.h"

int				ft_update_var(t_list *env, t_var *var, char *arg, int flags);
int				ft_add_var(t_list *env, char *arg, int flags);
static int		ft_assign_value(t_var *var, char *arg);
static t_var	*ft_create_var(char *str, int flags);

int	ft_update_var(t_list *env, t_var *var, char *arg, int flags)
{
	if ((flags & ENV_ASSIGN) == ENV_ASSIGN && ft_assign_value(var, arg) == -1)
		return (-1);
	if ((flags & ENV_EXP) == ENV_EXP)
	{
		env->n_exported += (var->exported == 0);
		var->exported = true;
	}
	return (0);
}

int	ft_add_var(t_list *env, char *arg, int flags)
{
	t_list_node	*node;
	t_var		*new_var;

	new_var = ft_create_var(arg, flags);
	node = ft_lstnew(new_var);
	if (node == NULL || new_var == NULL)
	{
		ft_free_content(new_var);
		return (-1);
	}
	ft_update_env_index(env, new_var, ADD);
	if (env->last_node == NULL)
		ft_lstadd_back(&env->list_node, node);
	else
		ft_lstadd_back(&env->last_node, node);
	env->last_node = node;
	env->n_exported += ((flags & ENV_EXP) == ENV_EXP);
	++env->n_var;
	return (0);
}

static int	ft_assign_value(t_var *var, char *arg)
{
	char	*value;

	value = ft_strdup(arg + ft_get_name_len(arg) + 1);
	if (value == NULL)
	{
		// perror?
		return (-1);
	}
	free(var->value);
	var->value = value;
	return (0);
}

static t_var	*ft_create_var(char *str, int flags)
{
	t_var		*new_var;
	size_t		name_len;

	new_var = ft_calloc(1, sizeof(t_var));
	if (new_var == NULL)
		return (NULL);
	name_len = ft_get_name_len(str);
	new_var->name = ft_strndup(str, name_len);
	if ((flags & ENV_ASSIGN) == ENV_ASSIGN)
		new_var->value = ft_strdup(str + name_len + 1);
	if (new_var->name == NULL \
		|| ((flags & ENV_ASSIGN) == ENV_ASSIGN && new_var->value == NULL))
		return (ft_freef("%p%p%p", new_var->name, new_var->value, new_var));
	if ((flags & ENV_EXP) == ENV_EXP)
		new_var->exported = true;
	return (new_var);
}
