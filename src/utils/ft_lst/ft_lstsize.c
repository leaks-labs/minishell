/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:45 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:58:46 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

size_t	ft_lstsize(t_list_node *list_node);

size_t	ft_lstsize(t_list_node *list_node)
{
	size_t	i;

	i = 0;
	while (list_node != NULL)
	{
		list_node = list_node->next;
		++i;
	}
	return (i);
}
