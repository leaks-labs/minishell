#include "ft_lst.h"
#include <stddef.h>

void	ft_lstclear(t_list **lst, del_func *del_func);

void	ft_lstclear(t_list **lst, del_func *del_func)
{
	void	*temp;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(temp, (del_func));
	}
}
