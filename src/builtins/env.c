#include "builtin.h"
#include "env.h"
#include <stdio.h>

int	ft_env(t_msh *msh, char **args);

int	ft_env(t_msh *msh, char **args)
{
	t_list_node	*node;
	t_var		*var;

	(void)args;
	node = msh->env.list_node;
	while (node != NULL)
	{
		var = (t_var *)node->content;
		if (var->exported == true && var->value != NULL)
			printf("%s=%s\n", var->name, var->value);
		node = node->next;
	}
	return (0);
}
