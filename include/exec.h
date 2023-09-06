#ifndef EXEC_H
# define EXEC_H

# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif

# include "utils.h"
# include "parse.h"

typedef struct msh
{
	char	**env;
	int		exit_status;
}				t_msh;

typedef enum exec_return
{
	EXEC_ERROR = -1,
	EXEC_EXIT = 0,
	EXEC_SUCCESS = 2
}			t_exec_return;

void			ft_run(t_msh *msh);
t_exec_return	ft_exec_line(t_msh *msh, t_pipeline *pipeline);

#endif
