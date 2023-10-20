#include "init.h"
#include "msh_signal.h"
#include <stddef.h>

int	main(int argc, char **argv, char **envp)
{
	t_msh	*msh;

	(void)argc;
	(void)argv;
	ft_set_signals(MSH_SIG_IGN);
	msh = ft_struct_init(envp);
	if (msh == NULL)
		return (NO_LAST_COMMAND);
	ft_run(msh);
	return (ft_quit(msh));
}
