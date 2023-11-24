/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:40 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:58:41 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list_node	*ft_lstlast(t_list_node *list_node);

t_list_node	*ft_lstlast(t_list_node *list_node)
{
	while (list_node != NULL && list_node->next != NULL)
		list_node = list_node->next;
	return (list_node);
}
