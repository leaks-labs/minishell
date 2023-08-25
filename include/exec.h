#ifndef EXEC_H
# define EXEC_H


#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

# include "utils.h"
# include "parse.h"


# define EXEC_ERROR -1
# define EXEC_EXIT 0
# define EXEC_SUCCESS 2

typedef struct msh
{
	char	**env;
	int		exit_status;
}				t_msh;

void 	ft_run(t_msh *msh);
int 	ft_exec_line(t_msh *msh, t_cmd_list *cmd_list);

#endif