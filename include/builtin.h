/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:01 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/25 01:50:00 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "parse.h"
# include <stdbool.h>

typedef struct msh	t_msh;
typedef struct list	t_list;
typedef int			(*t_built_f)(t_msh *, t_pl *, char **);

typedef enum builtins_list
{
	B_CD,
	B_ECHO,
	B_ENV,
	B_EXIT,
	B_EXPORT,
	B_PWD,
	B_UNSET,
	B_N_BUILTINS
}			t_builtins_list;

typedef struct builtins_entry
{
	const char	*name;
	t_built_f	func;
}				t_built_entry;

/*	GET_BUILTINS	*/
t_built_f	ft_get_builtin(char *cmd);

/*	CD	*/
int			ft_cd(t_msh *msh, t_pl *pl, char **args);
char		*ft_get_curpath(const char **args, t_msh *msh, bool *print_m);
t_list_node	*ft_get_cdpath(t_list *env);
/*	ECHO	*/
int			ft_echo(t_msh *msh, t_pl *pl, char **args);
/*	ENV	*/
int			ft_env(t_msh *msh, t_pl *pl, char **args);
/*	EXIT	*/
int			ft_exit(t_msh *msh, t_pl *pl, char **args);
/*	EXPORT	*/
int			ft_export(t_msh *msh, t_pl *pl, char **args);
/*	PWD	*/
int			ft_pwd(t_msh *msh, t_pl *pl, char **args);
/*	UNSET	*/
int			ft_unset(t_msh *msh, t_pl *pl, char **args);

#endif
