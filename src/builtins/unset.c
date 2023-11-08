#include "builtin.h"
#include "env.h"

int	ft_unset(t_list *env, char **args);

int	ft_unset(t_list *env, char **args)
{
	while (*args != NULL)
		ft_remove_var(env, *args++);
	return (0);
}
