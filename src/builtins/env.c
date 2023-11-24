/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:16 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:54:17 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include <stdio.h>

int	ft_env(t_msh *msh, t_pl *pl, char **args);

int	ft_env(t_msh *msh, t_pl *pl, char **args)
{
	t_list_node	*node;
	t_var		*var;

	(void)pl;
	(void)args;
	node = msh->env.list_node;
	while (node != NULL)
	{
		var = (t_var *)node->content;
		if (var->exported == true && var->value != NULL)
			printf("%s=%s\n", var->name, var->value);
		node = node->next;
	}
	return (0);
}
