#include "ft_lst.h"
#include <stddef.h>

t_list	*ft_lstlast(t_list *lst);

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
