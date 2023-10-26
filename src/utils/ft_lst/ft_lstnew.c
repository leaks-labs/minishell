#include "list.h"
#include "utils.h"

t_list_node	*ft_lstnew(void *content);

t_list_node	*ft_lstnew(void *content)
{
	t_list_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_list_node));
	if (new_node != NULL)
		new_node->content = content;
	return (new_node);
}
