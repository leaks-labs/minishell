/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:21 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:53:22 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtin.h"
# include "parse.h"
# include "list.h"
# include <stdint.h>

# define COMMAND_NOT_EXECUTABLE 126
# define COMMAND_NOT_FOUND 127

# define PROMPT "minishell$ "
# define HD_PROMPT "> "
# define MSH_ERROR_PROMPT "minishell: "

typedef struct list
{
	t_list_node	*list_node;
	t_list_node	*last_node;
	size_t		n_exported;
	size_t		n_var;
}				t_list;

typedef struct msh
{
	t_list			env;
	char			*cwd;
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
	t_list			*env;
	int				pipe[2];
	t_fd_io			s_fd_io;
	size_t			cmd_idx;
	size_t			n_cmd;
	pid_t			pid_last;
	unsigned int	*line_num;
}				t_exl;

typedef struct in_shell_pmt
{
	t_msh	*msh;
	t_pl	*pl;
	t_exl	*exl;
}				t_in_shell_pmt;

/*	EXEC	*/
uint8_t	ft_exec_line(t_msh *msh, t_pl *pl);
/*	IN_SHELL	*/
int		ft_in_shell(t_in_shell_pmt *pmt, t_cmd *cmd, t_built_f built_f);
/*	IN_SUBSHELL	*/
int		ft_in_subshell(t_msh *msh, t_exl *exl, t_pl *pl);
/*	RUN	*/
void	ft_run(t_msh *msh);
/*	WAIT	*/
int		ft_wait(pid_t last_pid);

#endif
