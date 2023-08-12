/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:21:47 by shinfray          #+#    #+#             */
/*   Updated: 2023/08/12 15:32:02 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "utils.h"

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

# define PROMPT "minishell$ "

typedef struct ms
{
	char	**env;
}				t_ms;


char	*ft_getenv(const char *name, char **env);

#endif