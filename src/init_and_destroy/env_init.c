#include "init.h"
#include "env.h"

int	ft_env_to_list(t_list *list, char **envp);

int	ft_env_to_list(t_list *list, char **envp)
{
	while (envp != NULL && *envp != NULL)
	{
		if (ft_add_var(list, *envp++, ENV_ASSIGN | ENV_EXP) == -1)
		{
			ft_lstclear(&list->list_node, &ft_free_var);
			return (-1);
		}
	}
	return (0);
}
