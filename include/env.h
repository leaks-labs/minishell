/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:16 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 22:59:38 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# define ENV_EXP 1
# define ENV_ASSIGN 2
# define ENV_APPEND 4
# define ENV_NOEXP 8

# include "exec.h"
# include <stdbool.h>

typedef enum idx_act
{
	ADD,
	REMOVE
}			t_idx_act;

typedef struct var
{
	const char	*name;
	char		*value;
	bool		exported;
	size_t		index;
}				t_var;

/*	ADD_VAR	*/
int		ft_add_var(t_list *env, const char *arg, int flags);
/*	CHECK_VAR	*/
bool	ft_isvalidname(const char *name);
bool	ft_isassignation(const char *str);
bool	ft_isappend(const char *str);
t_var	*ft_get_var(t_list *env, const char *name);
size_t	ft_get_name_len(const char *var);
/*	CONVERT_ENV	*/
int		ft_env_to_list(t_list *list, char **envp);
char	**ft_lst_to_env(t_list *env);
/*	MOD_VAR	*/
int		ft_mod_env2(t_list *env, const char *name, const char *val, int f);
int		ft_mod_env1(t_list *env, const char *arg, int f);
// int		ft_update_var(t_list *env, t_var *var, char *arg, int flags);
/*	REMOVE_VAR	*/
void	ft_remove_var(t_list *env, const char *name);
void	ft_free_content(void *content);
/*	SORT_ENV	*/
void	ft_update_env_index(t_list *env, t_var *var, t_idx_act e_idx_act);
t_var	*ft_get_var_per_index(t_list *env, size_t i);

#endif
