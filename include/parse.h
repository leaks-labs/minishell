/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:43 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:53:44 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <sys/types.h>
# include <stdint.h>
# include <stdbool.h>
# include "lexer.h"

typedef struct msh			t_msh;
typedef struct list_node	t_list_node;

typedef enum parse
{
	PARSE_ERROR = -1,
	PARSE_SUCCESS = 0,
	NOTHING_TO_PARSE = 1
}			t_parse;

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

typedef struct join
{
	char	*src;
	char	*dst;
	char	*tmp;
}				t_join;

typedef struct pl_args
{
	size_t	n_args;
	size_t	n_redirect;
}				t_pl_args;

typedef struct get
{
	size_t	i;
	size_t	j;
	size_t	k;
}				t_get;

t_parse		ft_parse(t_msh *msh, t_pl *pipeline, char *line);

void		ft_quoting(t_token_container *token_container);
uint8_t		ft_check_grammar(t_token_container *token_container);
uint8_t		ft_build_tree(t_pl *pipeline, t_token_container *token_container);

uint8_t		ft_alloc_pipeline(t_pl *pipeline, \
t_token_container *token_container);

size_t		ft_pipeline_len(t_token_container *token_container);
bool		ft_is_redir(t_lexer_operator e_operator_type);
t_io_type	ft_enum_swap(t_lexer_operator e_lexer_operator);

uint8_t		ft_check_expansion(t_msh *msh, t_token_container *token_container);
char		*ft_expansion_monitor(t_msh *msh, char *src, bool handle_quote);
uint8_t		ft_get_expansion_var(t_list_node **expansion_list, t_index *index, \
char *src);
uint8_t		ft_tokenise_expansion(t_list_node **node, t_index *index, \
char *src);
void		ft_get_flag(char *src, char *flag);
char		*ft_expand(t_msh *msh, char *src);

#endif
