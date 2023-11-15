#ifndef INIT_H
# define INIT_H

# include "exec.h"

# define NO_LAST_COMMAND 0
# define MAX_SHLVL 999
# define MAX_SHLVL_NUM_LEN 3

/*	STRUCT_DESTROY	*/
int		ft_quit(t_msh *msh);
void	ft_free_cmd_list(t_pl *pipeline);
/*	STRUCT_INIT	*/
t_msh	*ft_struct_init(char **envp);

#endif
