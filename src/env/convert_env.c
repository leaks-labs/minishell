/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:53 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:54:54 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"

int			ft_env_to_list(t_list *list, char **envp);
char		**ft_lst_to_env(t_list *env);
static char	*ft_one_var_to_str(t_var *var);

int	ft_env_to_list(t_list *list, char **envp)
{
	while (envp != NULL && *envp != NULL)
	{
		if (ft_add_var(list, *envp++, ENV_ASSIGN | ENV_EXP) == -1)
		{
			ft_lstclear(&list->list_node, &ft_free_content);
			return (-1);
		}
	}
	return (0);
}

char	**ft_lst_to_env(t_list *env)
{
	char		**export_env;
	t_list_node	*node;
	t_var		*var;
	size_t		i;

	export_env = ft_calloc(env->n_exported + 1, sizeof(char *));
	if (export_env == NULL)
		return (NULL);
	node = env->list_node;
	i = 0;
	while (node != NULL)
	{
		var = (t_var *)node->content;
		if (var->exported == true && var->value != NULL)
		{
			export_env[i] = ft_one_var_to_str((t_var *)node->content);
			if (export_env[i] == NULL)
				return (ft_freef("%P", export_env));
			++i;
		}
		node = node->next;
	}
	return (export_env);
}

static char	*ft_one_var_to_str(t_var *var)
{
	return (ft_join(3, var->name, "=", var->value));
}
