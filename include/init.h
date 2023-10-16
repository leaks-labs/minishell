#ifndef INIT_H
# define INIT_H

# include "exec.h"

# define NO_LAST_COMMAND 0

typedef enum init_return
{
	INIT_ERROR = -1,
	INIT_SUCCES = 0
}			t_init_return;

int		ft_quit(t_msh *msh);
t_msh	*ft_struct_init(char **envp);
void	ft_free_cmd_list(t_pipeline *pipeline);

#endif
