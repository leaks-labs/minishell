#ifndef EXEC_H
# define EXEC_H

# include "builtin.h"
# include "parse.h"
# include "list.h"
# include <stdbool.h>
# include <stdint.h>

# define COMMAND_NOT_EXECUTABLE 126
# define COMMAND_NOT_FOUND 127

# define PROMPT "minishell$ "
# define HD_PROMPT "> "
# define MSH_ERROR_PROMPT "minishell: "

typedef struct var
{
	char		*name;
	char		*value;
	bool		exported;
	size_t		index;
}				t_var;

typedef struct list
{
	t_list_node	*list_node;
	t_list_node	*last_node;
	size_t		n_exported;
	size_t		n_var;
}				t_list;

typedef struct msh
{
	t_list			env;
	char			**path;
	uint8_t			exit_status;
	unsigned int	line_num;
}				t_msh;

typedef struct fd_io
{
	int	fd_to_read;
	int	fd_to_write;
}				t_fd_io;

typedef struct exl
{
	t_list			*env;
	char			**path;
	int				pipe[2];
	t_fd_io			s_fd_io;
	ssize_t			cmd_idx;
	ssize_t			n_cmd;
	pid_t			pid_last;
	unsigned int	*line_num;
}				t_exl;

/*	EXEC_IN_SHELL	*/
int		ft_exec_in_shell(t_built_func built_func, t_exl *exl, t_cmd *cmd);
/*	EXEC_IN_SUBSHELL	*/
int		ft_exec_in_subshell(t_exl *exl, t_pipeline *pipeline);
/*	EXEC	*/
uint8_t	ft_exec_line(t_msh *msh, t_pipeline *pipeline);
/*	RUN	*/
void	ft_run(t_msh *msh);

#endif
