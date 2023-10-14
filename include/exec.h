#ifndef EXEC_H
# define EXEC_H

# include "parse.h"
# include <stdbool.h>

# define COMMAND_NOT_EXECUTABLE 126
# define COMMAND_NOT_FOUND 127
# define HD_PROMPT "> "
# define MSH_ERROR_PROMPT "minishell: "

typedef enum exec_return
{
	EXEC_ERROR = -1,
	EXEC_EXIT = 0,
	EXEC_SUCCESS = 2
}			t_exec_return;

typedef struct msh
{
	char	**env;
	int		line_num;
	int		exit_status;
}				t_msh;

typedef struct fd_io
{
	int	fd_to_read;
	int	fd_to_write;
}				t_fd_io;

typedef struct hd_node
{
	char			*hd_content;
	struct hd_node	*next;
}				t_hd_node;

typedef struct hd
{
	t_hd_node	*hd_list;
	t_hd_node	*last_node;
}				t_hd;

typedef struct exl
{
	char	**env;
	char	**path;
	int		pipe[2];
	t_fd_io	s_fd_io;
	ssize_t	cmd_idx;
	ssize_t	n_cmd;
	t_hd	hd;
	pid_t	pid_last;
	int		*line_num;
}				t_exl;

/*	CHILD_PROCESS	*/
void			ft_child_process(t_exl *exl, t_cmd *cmd);
/*	EXEC	*/
t_exec_return	ft_exec_line(t_msh *msh, t_pipeline *pipeline);
/*	GET_CMD_PATH	*/
char			*ft_get_cmd_path(char **path, char *cmd);
bool			ft_isapath(char *str);
/*	INIT_EXL	*/
int				ft_init_exl(t_exl *exl, t_msh *msh, t_pipeline *pipeline);
/*	RUN	*/
void			ft_run(t_msh *msh);

#endif
