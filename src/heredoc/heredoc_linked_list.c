#include "heredoc.h"
#include "utils.h"
#include <stdlib.h>

int			ft_update_hd_list(t_hd *hd, char *del, int *line_num);
void		ft_free_hd_list(t_hd *hd);
t_hd_node	*ft_delete_front_hd_node(t_hd_node *node);
static int	ft_append_hd_content(t_hd *hd, char *hd_content);

int	ft_update_hd_list(t_hd *hd, char *del, int *line_num)
{
	char	*hd_content;

	hd_content = ft_get_hd_content(del, line_num);
	if (hd_content == NULL)
	{
		ft_free_hd_list(hd);
		return (-1);
	}
	return (ft_append_hd_content(hd, hd_content));
}

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

static int	ft_append_hd_content(t_hd *hd, char *hd_content)
{
	t_hd_node	*new_hd_node;

	new_hd_node = ft_calloc(1, sizeof(t_hd_node));
	if (new_hd_node == NULL)
	{
		free(hd_content);
		ft_free_hd_list(hd);
		return (-1);
	}
	new_hd_node->hd_content = hd_content;
	if (hd->hd_list == NULL)
		hd->hd_list = new_hd_node;
	else
		hd->last_node->next = new_hd_node;
	hd->last_node = new_hd_node;
	return (0);
}
