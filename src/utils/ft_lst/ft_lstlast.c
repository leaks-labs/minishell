#include "list.h"
#include <stddef.h>

t_list_node	*ft_lstlast(t_list_node *list_node);

t_list_node	*ft_lstlast(t_list_node *list_node)
{
	while (list_node != NULL && list_node->next != NULL)
		list_node = list_node->next;
	return (list_node);
}
