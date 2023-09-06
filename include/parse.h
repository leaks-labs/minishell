#ifndef PARSE_H
#   define PARSE_H

# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifdef __linux__
#  include <sys/types.h>
# endif

# define PROMPT "minishell$ "

typedef struct msh_args
{
    size_t msh_argc;
    char **msh_argv;
}               t_msh_args;

typedef	enum io_type
{
	INPUT,
	HEREDOC,
	OUTPUT,
	APPEND
}			t_io_type;

typedef	struct redirect
{
	char		*file;
	t_io_type	e_iotype;
}				t_redirect;

typedef struct cmd
{
	char		**args;
	t_redirect	*redirect_arr;
	ssize_t		n_redirect;
}                t_cmd;

typedef struct pipeline
{
	t_cmd	*cmd_list;
	ssize_t	n_cmd;
}				t_pipeline;

typedef enum parse_return
{
	PARSE_ERROR  = -1,
	PARSE_SUCCESS =  0
}			t_parse_return;


t_parse_return 	ft_parse(t_pipeline *pipeline, char *line);

#endif
