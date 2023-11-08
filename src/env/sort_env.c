#include "env.h"
#include "utils.h"

void	ft_set_index(t_list *env, t_var *new_var);
t_var	*ft_get_var_per_index(t_list *env, size_t i);

void	ft_set_index(t_list *env, t_var *new_var)
{
	t_list_node *node;
	t_var		*env_var;

	if (env->list_node == NULL)
		return ;
	node = env->list_node;
	while (node != NULL)
	{
		env_var = (t_var *)node->content;
		if (ft_strcmp(env_var->name, new_var->name) < 0)
			++new_var->index;
		else
			++env_var->index;
		node = node->next;
	}
}

t_var	*ft_get_var_per_index(t_list *env, size_t i)
{
	t_list_node	*node;
	t_var		*var;

	node = env->list_node;
	while (node != NULL)
	{
		var = ((t_var *)node->content);
		if (i != var->index)
			node = node->next;
		else
			return (var);
	}
	return (NULL);
}
