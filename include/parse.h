#ifndef PARSE_H
#   define PARSE_H

# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$ "

typedef struct msh_args
{
    size_t msh_argc;
    char **msh_argv;
}               t_msh_args;

typedef	enum io_type
{
	SIMPLE,
	DOUBLE
}			t_io_type;

typedef	struct redirect_in
{
	char		*infile;
	t_io_type	e_iotype;
}				t_redirect_in;

typedef	struct redirect_out
{
	char		*outfile;
	t_io_type	e_iotype;
}				t_redirect_out;

typedef struct cmd
{
	char			**args;
	t_redirect_in	*infile_arr;
	t_redirect_out	*outfile_arr;
	size_t			n_infile;
	size_t			n_outfile;
}                t_cmd;

typedef struct cmd_list
{
	t_cmd	*cmd_list;
	size_t	n_cmd;
}				t_cmd_list;

typedef enum parse_return
{
	PARSE_ERROR  = -1,
	PARSE_SUCCESS =  0
}			t_parse_return;


t_parse_return 	ft_parse(t_cmd_list *cmd_list, char *line);

#endif
