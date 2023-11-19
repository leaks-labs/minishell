#include "list.h"

void	ft_lstadd_back(t_list_node **list_node, t_list_node *new_node);

void	ft_lstadd_back(t_list_node **list_node, t_list_node *new_node)
{
	if (list_node == NULL)
		return ;
	if (*list_node == NULL)
		*list_node = new_node;
	else
		ft_lstlast(*list_node)->next = new_node;
}
