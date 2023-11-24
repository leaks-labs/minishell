/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:32 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:53:33 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <sys/types.h>

# define NO_OCCURRENCE -1
# define OPERATOR 0
# define OPERATOR_LEN_MAX 3

typedef enum lexer
{
	LEXED,
	NOT_LEXED
}			t_lexer;

typedef enum node_type
{
	NODE,
	SENTINEL_NODE
}			t_node_type;

typedef enum lexer_operator
{
	HERE_DOC,
	INPUT,
	APPEND,
	OUTPUT,
	PIPE,
	NO_OPERATOR,
	DICTIONARY_SIZE
}			t_lexer_operator;

typedef struct index
{
	size_t	current;
	size_t	previous;
}				t_index;

typedef struct dictionary
{
	t_lexer_operator	operator_type;
	size_t				len;
	char				operator[OPERATOR_LEN_MAX];
}			t_dictionary;

typedef struct token
{
	t_lexer_operator	operator_type;
	char				*token;
}			t_token;

typedef struct s_token_list
{
	struct s_token_list	*next;
	struct s_token_list	*prev;
	t_node_type			node_type;
	t_token				*struct_token;
}				t_token_list;

typedef struct token_container
{
	t_token_list	*sentinel_node;
	size_t			list_size;
}				t_token_container;

t_token_container	*ft_lexer_monitor(char *line);
t_dictionary		ft_search_operator(char *line);

t_lexer				ft_get_token(t_token_container *token_container, \
char *line, t_lexer_operator operator, t_index *index);
t_lexer				ft_skip_quotes(char *line, t_index *index);
void				ft_get_next_index(char *line, t_index *index);

t_token_container	*ft_create_list(void);
void				ft_delete_list(t_token_container	*token_container);
void				ft_delete_node(t_token_container *token_container, \
t_token_list *node_to_del);
t_token				*ft_tokenise(t_lexer_operator operator_type, char *line, \
t_index *index);
t_token_list		*ft_append(t_token_container *token_container, \
t_token *struct_token);

#endif