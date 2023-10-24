#include "ft_lst.h"
#include <stddef.h>

size_t	ft_lstsize(t_list *lst);

size_t	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		++i;
	}
	return (i);
}
