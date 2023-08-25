#ifndef INIT_H
# define INIT_H

#include "exec.h"

# define INIT_SUCCES 0 //is it used ?
# define INIT_ERROR -1

int     ft_init_args(t_msh_args *msh_args, char *line);
int     ft_quit(t_msh *msh);
t_msh   *ft_struct_init(char **envp);

#endif