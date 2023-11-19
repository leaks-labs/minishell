#include "list.h"

size_t	ft_lstsize(t_list_node *list_node);

size_t	ft_lstsize(t_list_node *list_node)
{
	size_t	i;

	i = 0;
	while (list_node != NULL)
	{
		list_node = list_node->next;
		++i;
	}
	return (i);
}
