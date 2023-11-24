/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:35 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:53:36 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stddef.h>

typedef void	(del_func)(void *);

typedef struct list_node
{
	void				*content;
	struct list_node	*next;
}				t_list_node;

void		ft_lstadd_back(t_list_node **list_node, t_list_node *new_node);
void		ft_lstadd_front(t_list_node **list_node, t_list_node *new_node);
void		ft_lstclear(t_list_node **list_node, del_func *del_func);
void		ft_lstdelone(t_list_node *list_node, del_func *del_func);
t_list_node	*ft_lstlast(t_list_node *list_node);
t_list_node	*ft_lstnew(void *content);
size_t		ft_lstsize(t_list_node *list_node);

#endif
