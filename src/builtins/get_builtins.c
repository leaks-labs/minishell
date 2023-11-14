#include "builtin.h"
#include "utils.h"

t_built_f	ft_get_builtin(char *cmd);

t_built_f	ft_get_builtin(char *cmd)
{
	const t_built_entry	built_dic[N_BUILTINS + 1] = {{"cd", &ft_cd}, \
													{"echo", &ft_echo}, \
													{"env", &ft_env}, \
													{"exit", &ft_exit}, \
													{"export", &ft_export}, \
													{"pwd", &ft_pwd}, \
													{"unset", &ft_unset}};
	const t_built_entry	*tmp_entry;

	if (cmd == NULL)
		return (NULL);
	tmp_entry = built_dic;
	while (tmp_entry->name != NULL && ft_strcmp(cmd, tmp_entry->name) != 0)
		++tmp_entry;
	return (tmp_entry->func);
}
