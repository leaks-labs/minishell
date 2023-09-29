/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:12:02 by shinfray          #+#    #+#             */
/*   Updated: 2023/09/15 10:14:37 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int				ft_init_exl(t_exl *exl, t_msh *msh, t_pipeline *pipeline);
static char		**ft_get_path(char **envp);
static char		**ft_set_slash(char **path);

int	ft_init_exl(t_exl *exl, t_msh *msh, t_pipeline *pipeline)
{
	exl->env = msh->env;
	exl->path = ft_get_path(msh->env);
	exl->cmd_idx = -1;
	exl->n_cmd = pipeline->n_cmd;
	return (ft_heredoc(pipeline->cmd_list, exl));
}

static char	**ft_get_path(char **envp)
{
	char	**path;

	path = ft_split(ft_getenv("PATH", envp), ':');
	if (path == NULL)
		return (NULL);
	return (ft_set_slash(path));
}

static char	**ft_set_slash(char **path)
{
	char	*temp;
	int		i;

	i = 0;
	while (path != NULL && path[i] != NULL)
	{
		temp = ft_join(2, path[i], "/");
		if (temp == NULL)
		{
			// perror("ft_strjoin");
			return (ft_freef("%P", path));
		}
		free(path[i]);
		path[i++] = temp;
	}
	return (path);
}
