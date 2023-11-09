#ifndef ENV_H
# define ENV_H

# define ENV_EXP 1
# define ENV_ASSIGN 2

# include "exec.h"
# include <stdbool.h>

typedef enum idx_act
{
	ADD,
	REMOVE
}			t_idx_act;

/*	CHECK_VAR	*/
bool	ft_isvalidname(const char *name);
bool	ft_isassignation(const char *str);
t_var	*ft_get_var(t_list *env, char *name);
size_t	ft_get_name_len(const char *var);
/*	CONVERT_ENV	*/
int		ft_env_to_list(t_list *list, char **envp);
char	**ft_lst_to_env(t_list *env);
/*	MOD_AND_ADD_VAR	*/
int		ft_update_var(t_list *env, t_var *var, char *arg, int flags);
int		ft_add_var(t_list *env, char *arg, int flags);
/*	REMOVE_VAR	*/
void	ft_remove_var(t_list *env, char *name);
void	ft_free_content(void *content);
/*	SORT_ENV	*/
void	ft_update_env_index(t_list *env, t_var *var, t_idx_act e_idx_act);
t_var	*ft_get_var_per_index(t_list *env, size_t i);

#endif