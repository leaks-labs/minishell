#include "ft_lst.h"
#include "utils.h"

t_list	*ft_lstnew(void *content);

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (new_node != NULL)
		new_node->content = content;
	return (new_node);
}
