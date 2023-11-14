#ifndef HEREDOC_H
# define HEREDOC_H

# include "exec.h"

/*	HEREDOC	*/
int		ft_heredoc(t_cmd *cmd_list, t_exl *exl);
/*	RETRIEVE_HD_CONTENT	*/
char	*ft_get_hd_content(char *del, unsigned int *line_num);

#endif
