/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:42 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:58:43 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "utils.h"

t_list_node	*ft_lstnew(void *content);

t_list_node	*ft_lstnew(void *content)
{
	t_list_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_list_node));
	if (new_node != NULL)
		new_node->content = content;
	return (new_node);
}
