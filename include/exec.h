#ifndef EXEC_H
# define EXEC_H

# include "parse.h"
# include <stdbool.h>

# define COMMAND_NOT_EXECUTABLE 126
# define COMMAND_NOT_FOUND 127

# define PROMPT "minishell$ "
# define HD_PROMPT "> "
# define MSH_ERROR_PROMPT "minishell: "

typedef struct msh
{
	char			**env;
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
	char			**env;
	char			**path;
	int				pipe[2];
	t_fd_io			s_fd_io;
	ssize_t			cmd_idx;
	ssize_t			n_cmd;
	pid_t			pid_last;
	unsigned int	*line_num;
}				t_exl;

/*	CHILD_PROCESS	*/
pid_t	ft_child_process(t_exl *exl, t_cmd *cmd);
/*	EXEC	*/
uint8_t	ft_exec_line(t_msh *msh, t_pipeline *pipeline);
/*	GET_CMD_PATH	*/
char	*ft_get_cmd_path(char **path, char *cmd);
bool	ft_isapath(char *str);
/*	GET_PATH	*/
char	**ft_get_path(char **envp);
/*	RUN	*/
void	ft_run(t_msh *msh);

#endif
