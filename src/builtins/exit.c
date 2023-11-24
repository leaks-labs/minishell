/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:19 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:54:20 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "init.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>

int	ft_exit(t_msh *msh, t_pl *pl, char **args);

int	ft_exit(t_msh *msh, t_pl *pl, char **args)
{
	uint8_t	exit_code;
	bool	error;

	ft_putendl_fd("exit", STDERR_FILENO);
	exit_code = msh->exit_status;
	error = false;
	if (args != NULL && args[0] != NULL)
	{
		exit_code = (uint8_t)ft_strtoimax(*args, &error);
		if (error == true)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(*args, STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit_code = 2;
		}
		else if (args[1] != NULL)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
	}
	ft_free_cmd_list(pl);
	msh->exit_status = exit_code;
	exit(ft_quit(msh));
}
