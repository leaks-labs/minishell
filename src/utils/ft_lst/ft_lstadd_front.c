#include "list.h"
#include <stddef.h>

void	ft_lstadd_front(t_list_node **list_node, t_list_node *new_node);

void	ft_lstadd_front(t_list_node **list_node, t_list_node *new_node)
{
	if (new_node == NULL || list_node == NULL)
		return ;
	new_node->next = *list_node;
	*list_node = new_node;
}
