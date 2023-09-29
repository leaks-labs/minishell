#ifndef EXEC_H
# define EXEC_H

# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif

# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include "parse.h"
# include "utils.h"

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

typedef enum hd_return
{
	HD_ERROR = -1,
	HD_SUCCESS = 0,
	NO_HD = 1
}			t_hd_return;

typedef struct msh
{
	char	**env;
	int		exit_status;
}				t_msh;

typedef	struct fd_io
{
	int	fd_to_read;
	int	fd_to_write;
}				t_fd_io;

typedef	struct hd_node
{
	char			*hd_content;
	struct hd_node	*next;
}				t_hd_node;

typedef	struct hd
{
	t_hd_node	*hd_list;
	t_hd_node	*last_node;
}				t_hd;

typedef	struct exl
{
	char		**env;
	char		**path;
	int			pipe[2];
	t_fd_io		s_fd_io;
	ssize_t		cmd_idx;
	ssize_t		n_cmd;
	t_hd		hd;
	pid_t		pid_last;
}				t_exl;

/*	ADAPT_REDIRECTIONS	*/
int				ft_set_input(t_exl *exl, char *file);
int				ft_set_heredoc(t_exl *exl, char *file);
int				ft_set_output(t_exl *exl, char *file);
int				ft_set_append(t_exl *exl, char *file);
/*	CHILD_PROCESS	*/
void			ft_child_process(t_exl *exl, t_cmd *cmd);
/*	EXEC	*/
t_exec_return	ft_exec_line(t_msh *msh, t_pipeline *pipeline);
/*	GET_CMD_PATH	*/
char			*ft_get_cmd_path(char **path, char *cmd);
bool			ft_isapath(char *str);
/*	HEREDOC_LINKED_LIST_UTILS	*/
void			ft_free_hd_list(t_hd *hd);
t_hd_node		*ft_delete_front_hd_node(t_hd_node *node);
/*	HEREDOC	*/
int				ft_heredoc(t_cmd *cmd_list, t_exl *exl);
/*	INIT_EXL	*/
int				ft_init_exl(t_exl *exl, t_msh *msh, t_pipeline *pipeline);
/*	REDIRECTIONS_UTILS	*/
int				ft_createpipe(int *pp);
void			ft_close_used_pipes(t_fd_io *fd_io);
bool			ft_islastcmd(t_exl *exl);
/*	REDIRECTIONS	*/
int				ft_set_redirections(t_exl *exl, t_cmd *cmd);
uint8_t			ft_apply_redirections(t_exl *exl);
/*	RUN	*/
void			ft_run(t_msh *msh);

#endif
