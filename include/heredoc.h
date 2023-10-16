#ifndef HEREDOC_H
# define HEREDOC_H

# include "exec.h"
# include "parse.h"

/*	HEREDOC_LINKED_LIST	*/
int			ft_update_hd_list(t_hd *hd, char *del, unsigned int *line_num);
void		ft_free_hd_list(t_hd *hd);
t_hd_node	*ft_delete_front_hd_node(t_hd_node *node);
/*	HEREDOC	*/
int			ft_heredoc(t_cmd *cmd_list, t_exl *exl);
char		*ft_get_hd_content(char *del, unsigned int *line_num);

#endif