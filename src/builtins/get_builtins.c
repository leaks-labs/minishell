#include "builtin.h"
#include "utils.h"

t_built_func	ft_get_builtin(char *cmd);

t_built_func	ft_get_builtin(char *cmd)
{
	const t_built_entry	builtins_dic[N_BUILTINS + 1] = {{"echo", &ft_echo}, \
														{"env", &ft_env}};
	const t_built_entry	*tmp_entry;

	tmp_entry = builtins_dic;
	while (tmp_entry->name != NULL && ft_strcmp(cmd, tmp_entry->name) != 0)
		++tmp_entry;
	return (tmp_entry->func);
}