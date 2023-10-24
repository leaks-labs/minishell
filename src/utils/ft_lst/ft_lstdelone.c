#include "ft_lst.h"
#include <stddef.h>
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, del_func *del_func);

void	ft_lstdelone(t_list *lst, del_func *del_func)
{
	if (lst != NULL)
		return ;
	if ((del_func) != NULL)
		(*del_func)(lst->content);
	else
		free(lst->content);
	free(lst);
}
