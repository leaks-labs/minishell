/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:36 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:54:37 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"

int	ft_unset(t_msh *msh, t_pl *pl, char **args);

int	ft_unset(t_msh *msh, t_pl *pl, char **args)
{
	(void)pl;
	while (*args != NULL)
		ft_remove_var(&msh->env, *args++);
	return (0);
}
