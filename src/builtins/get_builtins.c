/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:30 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:54:31 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

t_built_f	ft_get_builtin(char *cmd);

t_built_f	ft_get_builtin(char *cmd)
{
	const t_built_entry	built_dic[B_N_BUILTINS + 1] = {{"cd", &ft_cd}, \
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
