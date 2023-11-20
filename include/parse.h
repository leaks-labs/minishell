#ifndef PARSE_H
# define PARSE_H

# include <sys/types.h>
# include <stdint.h>
//# include "lexer.h"

typedef struct msh	t_msh;
typedef struct token_container t_token_container;

typedef enum io_type
{
	IO_INPUT,
	IO_HEREDOC,
	IO_OUTPUT,
	IO_APPEND
}			t_io_type;

typedef struct redirect
{
	char		*file;
	t_io_type	e_iotype;
}				t_redirect;

typedef struct cmd
{
	char		**args;
	t_redirect	*redirect_arr;
	size_t		n_redirect;
}				t_cmd;

typedef struct pipeline
{
	t_cmd	*cmd_list;
	size_t	n_cmd;
}				t_pl;

uint8_t	ft_parse(t_msh *msh, t_pl *pipeline, char *line);
uint8_t ft_check_expansion(t_msh *msh, t_token_container *token_container);


#endif
