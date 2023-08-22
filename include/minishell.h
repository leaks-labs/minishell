/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:21:47 by shinfray          #+#    #+#             */
/*   Updated: 2023/08/22 13:18:50 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "utils.h"

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

# define PROMPT "minishell$ "
//run
# define RUN_ERROR -1
# define RUN_SUCCESS 0
//parse
# define PARSE_ERROR -1
# define PARSE_SUCCESS 0
//exec
# define EXEC_ERROR -1
# define EXEC_SUCCESS 0
# define EXEC_EXIT 1

typedef struct msh
{
	char	**env;
	int		exit_status;
}				t_msh;

typedef struct cmd
{
	char **cmd;
}				t_cmd;


//exec
int 	ft_run(t_msh *msh);
int 	ft_exec_line(t_msh *msh, t_cmd *cmd);

//init
int 	ft_quit(t_msh *msh);
t_msh *ft_struct_init(char **envp);

//parse
int 	ft_parse(t_cmd *cmd, char *line);

//utils
char	*ft_getenv(const char *name, char **env);

#endif