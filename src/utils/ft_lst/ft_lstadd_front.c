/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:32 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:58:33 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_lstadd_front(t_list_node **list_node, t_list_node *new_node);

void	ft_lstadd_front(t_list_node **list_node, t_list_node *new_node)
{
	if (new_node == NULL || list_node == NULL)
		return ;
	new_node->next = *list_node;
	*list_node = new_node;
}
