#include "utils.h"
#include "env.h"

char	*ft_getenv(const char *name, t_list *env);

char	*ft_getenv(const char *name, t_list *env)
{
	t_list_node	*node;

	node = env->list_node;
	while (node != NULL && ft_strcmp(name, ((t_var *)node->content)->name) != 0)
		node = node->next;
	if (node != NULL)
		return (((t_var *)node->content)->value);
	return (NULL);
}
