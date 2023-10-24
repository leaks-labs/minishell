#ifndef FT_LST_H
# define FT_LST_H

# include <stddef.h>

typedef void	(del_func)(void *);

typedef struct list
{
	void		*content;
	struct list	*next;
}				t_list;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, del_func *del_func);
void	ft_lstdelone(t_list *lst, del_func *del_func);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
size_t	ft_lstsize(t_list *lst);

#endif
