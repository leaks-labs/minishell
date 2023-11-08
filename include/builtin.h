#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct list	t_list;
typedef int			(*t_built_func)(t_list *, char **);

typedef enum builtins_list
{
	ECHO,
	ENV,
	EXPORT,
	N_BUILTINS
}			t_builtins_list;

typedef struct builtins_entry
{
	const char		*name;
	t_built_func	func;
}				t_built_entry;

/*	ECHO	*/
int				ft_echo(t_list *env, char **args);
/*	ENV	*/
int				ft_env(t_list *env, char **args);
/*	EXPORT	*/
int				ft_export(t_list *env, char **args);
/*	GET_BUILTINS	*/
t_built_func	ft_get_builtin(char *cmd);

#endif