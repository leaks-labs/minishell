/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:30 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:58:31 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_lstadd_back(t_list_node **list_node, t_list_node *new_node);

void	ft_lstadd_back(t_list_node **list_node, t_list_node *new_node)
{
	if (list_node == NULL)
		return ;
	if (*list_node == NULL)
		*list_node = new_node;
	else
		ft_lstlast(*list_node)->next = new_node;
}
