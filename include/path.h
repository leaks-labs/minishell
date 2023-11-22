#ifndef PATH_H
# define PATH_H

# include "exec.h"

/*	GET_CMD_PATH	*/
char		*ft_get_cmd_path(t_list_node *path, const char *cmd);
bool		ft_isapath(const char *str);
/*	GET_PATH	*/
t_list_node	*ft_get_path(t_list *env);

#endif
