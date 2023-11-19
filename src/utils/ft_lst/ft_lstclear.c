#include "list.h"

void	ft_lstclear(t_list_node **list_node, del_func *del_func);

void	ft_lstclear(t_list_node **list_node, del_func *del_func)
{
	void	*temp;

	if (list_node == NULL)
		return ;
	while (*list_node != NULL)
	{
		temp = *list_node;
		*list_node = (*list_node)->next;
		ft_lstdelone(temp, (del_func));
	}
}
