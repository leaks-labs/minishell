#ifndef ENV_H
# define ENV_H

# define ENV_EXP 1
# define ENV_ASSIGN 2

# include "exec.h"
# include <stdbool.h>

/*	CHECK_VAR	*/
bool	ft_isvalidname(const char *name);
bool	ft_isassignation(const char *str);
t_var	*ft_get_var(t_list *env, char *name);
size_t	ft_get_name_len(const char *var);
/*	MOD_VAR	*/
int		ft_update_var(t_list *env, t_var *var, char *arg, int flags);
int		ft_add_var(t_list *env, char *arg, int flags);
void	ft_free_var(void *content);

#endif