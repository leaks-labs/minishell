#include "builtin.h"
#include "utils.h"
#include <stdio.h>

int	ft_echo(t_msh *msh, t_pl *pl, char **args);

int	ft_echo(t_msh *msh, t_pl *pl, char **args)
{
	bool	no_nl;

	(void)msh;
	(void)pl;
	if (*args != NULL)
	{
		no_nl = (ft_strcmp(*args, "-n") == 0);
		if (no_nl == true)
			++args;
	}
	while (*args != NULL)
	{
		printf("%s", *args++);
		if (*args != NULL)
			printf(" ");
	}
	if (no_nl == false)
		printf("\n");
	return (0);
}
