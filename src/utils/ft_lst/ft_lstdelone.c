#include "list.h"
#include <stddef.h>
#include <stdlib.h>

void	ft_lstdelone(t_list_node *list_node, del_func *del_func);

void	ft_lstdelone(t_list_node *list_node, del_func *del_func)
{
	if (list_node != NULL)
		return ;
	if ((del_func) != NULL)
		(*del_func)(list_node->content);
	else
		free(list_node->content);
	free(list_node);
}
