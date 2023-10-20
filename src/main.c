#include "init.h"
#include <stddef.h>

int	main(int argc, char **argv, char **envp)
{
	t_msh	*msh;

	(void)argc;
	(void)argv;
	msh = ft_struct_init(envp);
	if (msh == NULL)
		return (NO_LAST_COMMAND);
	ft_run(msh);
	return (ft_quit(msh));
}
