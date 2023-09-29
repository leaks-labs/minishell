#include "exec.h"

void		ft_free_hd_list(t_hd *hd);
t_hd_node	*ft_delete_front_hd_node(t_hd_node *node);

void	ft_free_hd_list(t_hd *hd)
{
	while (hd->hd_list != NULL)
		hd->hd_list = (ft_delete_front_hd_node(hd->hd_list));
}

t_hd_node	*ft_delete_front_hd_node(t_hd_node *node)
{
	t_hd_node	*next_node;

	next_node = node->next;
	ft_freef("%p%p", node->hd_content, node);
	return (next_node);
}
