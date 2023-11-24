/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:21 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:58:22 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "msh_signal.h"

int	main(int argc, char **argv, char **envp)
{
	t_msh	*msh;

	(void)argc;
	(void)argv;
	ft_set_signals(MSH_SIG_IGN);
	msh = ft_struct_init(envp);
	if (msh == NULL)
		return (NO_LAST_COMMAND);
	ft_run(msh);
	return (ft_quit(msh));
}
