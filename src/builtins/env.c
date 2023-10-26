#include "builtin.h"
#include <stdio.h>

int	ft_env(t_list *env, char ** args);

int	ft_env(t_list *env, char **args)
{
	t_list_node	*node;
	t_var		*var;

	(void)args;
	node = env->list_node;
	while (env != NULL && node != NULL)
	{
		var = (t_var *)node->content;
		if (var->exported == true)
			printf("%s=%s\n", var->name, var->value);
		node = node->next;
	}
	return (0);
}