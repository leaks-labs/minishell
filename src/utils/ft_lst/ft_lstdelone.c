/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:37 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:58:38 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>

void	ft_lstdelone(t_list_node *list_node, del_func *del_func);

void	ft_lstdelone(t_list_node *list_node, del_func *del_func)
{
	if (list_node == NULL)
		return ;
	if ((del_func) != NULL)
		(*del_func)(list_node->content);
	else
		free(list_node->content);
	free(list_node);
}
