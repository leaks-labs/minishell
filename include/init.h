#ifndef INIT_H
# define INIT_H

# include "exec.h"

# define NO_LAST_COMMAND 0

/*	ENV_INIT	*/
int		ft_env_to_list(t_list *list, char **envp);
void	ft_free_var(void *content);
/*	STRUCT_DESTROY	*/
int		ft_quit(t_msh *msh);
void	ft_free_cmd_list(t_pipeline *pipeline);
/*	STRUCT_INIT	*/
t_msh	*ft_struct_init(char **envp);

#endif
