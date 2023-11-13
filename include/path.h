#ifndef PATH_H
# define PATH_H

# include "exec.h"

/*	GET_CMD_PATH	*/
char	*ft_get_cmd_path(char **path, char *cmd);
bool	ft_isapath(const char *str);
/*	GET_PATH	*/
char	**ft_get_path(t_list *env);

#endif