/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:33 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:54:34 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int			ft_pwd(t_msh *msh, t_pl *pl, char **args);
static int	ft_pwd_fallback(void);

int	ft_pwd(t_msh *msh, t_pl *pl, char **args)
{
	(void)pl;
	(void)args;
	if (msh->cwd == NULL)
		return (ft_pwd_fallback());
	else
		printf("%s\n", msh->cwd);
	return (0);
}

static int	ft_pwd_fallback(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (1);
	printf("%s\n", path);
	free(path);
	return (0);
}
