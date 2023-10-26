#include "init.h"
#include "utils.h"

int				ft_env_to_list(t_list *list, char **envp);
void			ft_free_var(void *content);
static t_var	*ft_create_var(char *str);
static size_t	ft_get_name_len(const char *var);

int	ft_env_to_list(t_list *list, char **envp)
{
	t_var		*new_var;
	t_list_node	*node;

	while (envp != NULL && *envp != NULL)
	{
		new_var = ft_create_var(*envp);
		node = ft_lstnew(new_var);
		if (node == NULL || new_var == NULL)
		{
			ft_free_var(new_var);
			ft_lstclear(&list->list_node, &ft_free_var);
			return (-1);
		}
		if (list->last_node == NULL)
			ft_lstadd_back(&list->list_node, node);
		else
			ft_lstadd_back(&list->last_node, node);
		list->last_node = node;
		++list->n_exported;
		++envp;
	}
	return (0);
}

void	ft_free_var(void *content)
{
	t_var	*var;

	if (content == NULL)
		return ;
	var = (t_var *)content;
	ft_freef("%p%p%p", var->name, var->value, var);
}

static t_var	*ft_create_var(char *str)
{
	t_var		*new_var;
	size_t		name_len;

	new_var = ft_calloc(1, sizeof(t_var));
	if (new_var == NULL)
		return (NULL);
	name_len = ft_get_name_len(str);
	new_var->name = ft_strndup(str, name_len);
	new_var->value = ft_strdup(str + name_len + 1);
	if (new_var->name == NULL || new_var->value == NULL)
		return (ft_freef("%p%p%p", new_var->name, new_var->value, new_var));
	new_var->exported = true;
	return (new_var);
}

static size_t	ft_get_name_len(const char *var)
{
	const char	*tmp;

	tmp = var;
	while (*tmp != '=')
		++tmp;
	return ((size_t)(tmp - var));
}
