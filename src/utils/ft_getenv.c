/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:57:13 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:57:14 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "env.h"

char	*ft_getenv(const char *name, const t_list *env);

char	*ft_getenv(const char *name, const t_list *env)
{
	t_list_node	*node;

	node = env->list_node;
	while (node != NULL && ft_strcmp(name, ((t_var *)node->content)->name) != 0)
		node = node->next;
	if (node != NULL)
		return (((t_var *)node->content)->value);
	return (NULL);
}
