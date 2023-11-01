#ifndef BUILTIN_H
# define BUILTIN_H

# include "exec.h"

typedef int	(*t_built_func)(t_list *, char **);

typedef enum builtins_list
{
	ECHO,
	ENV,
	N_BUILTINS = ENV
}			t_builtins_list;

typedef struct builtins_entry
{
	const char		*name;
	t_built_func	func;
}				t_built_entry;

t_built_func	ft_get_builtin(char *cmd);

int				ft_echo(t_list *env, char ** args);
int				ft_env(t_list *env, char **args);

#endif