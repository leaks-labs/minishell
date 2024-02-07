/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:16 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:54:17 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include <stdio.h>

int			ft_echo(t_msh *msh, t_pl *pl, char **args);
static bool	ft_check_n_flag(char *arg, bool *flag);

int	ft_echo(t_msh *msh, t_pl *pl, char **args)
{
	bool	no_nl;

	(void)msh;
	(void)pl;
	no_nl = false;
	while (*args != NULL && ft_check_n_flag(*args, &no_nl) == true)
		++args;
	while (*args != NULL)
	{
		printf("%s", *args++);
		if (*args != NULL)
			printf(" ");
	}
	if (no_nl == false)
		printf("\n");
	return (0);
}

static bool	ft_check_n_flag(char *arg, bool *flag)
{
	if (ft_strncmp(arg, "-n", 2) != 0)
		return (false);
	arg += 2;
	while (*arg == 'n')
		++arg;
	if (*arg == '\0')
	{
		*flag = true;
		return (true);
	}
	return (false);
}
