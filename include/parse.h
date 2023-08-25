#ifndef PARSE_H
#   define PARSE_H

# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PARSE_ERROR -1
# define PARSE_SUCCESS 0

# define PROMPT "minishell$ "

typedef struct msh_args
{
    int argc;
    char **argv;
}               t_msh_args;

typedef struct cmd
{
	char	**cmd;
}				t_cmd;

typedef struct cmd_list
{
	t_cmd	*cmd_list;
	size_t	n_cmd;
	char	*infile;
	char	*outfile;
	bool	here_doc;
	bool	append;
}				t_cmd_list;


int 	ft_parse(t_cmd_list *cmd_list, char *line);

#endif