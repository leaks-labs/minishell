#include "builtin.h"
#include "utils.h"
#include <stdio.h>

int	ft_echo(t_list *env, char **args);

int	ft_echo(t_list *env, char **args)
{
	bool	no_nl;

	(void)env;
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