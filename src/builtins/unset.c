#include "builtin.h"
#include "env.h"

int	ft_unset(t_msh *msh, t_pl *pl, char **args);

int	ft_unset(t_msh *msh, t_pl *pl, char **args)
{
	(void)pl;
	while (*args != NULL)
		ft_remove_var(&msh->env, *args++);
	return (0);
}
