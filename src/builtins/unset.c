#include "builtin.h"
#include "env.h"

int	ft_unset(t_msh *msh, char **args);

int	ft_unset(t_msh *msh, char **args)
{
	while (*args != NULL)
		ft_remove_var(&msh->env, *args++);
	return (0);
}
