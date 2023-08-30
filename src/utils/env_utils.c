/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:23:28 by shinfray          #+#    #+#             */
/*   Updated: 2023/08/12 16:40:53y shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char			*ft_getenv(const char *name, char **env);

char	*ft_getenv(const char *name, char **env)
{
	while (env != NULL && *env != NULL \
			&& (ft_strncmp(*env, name, ft_strlen(name)) != 0 \
			|| (*env)[ft_strlen(name)] != '='))
		++env;
	if (env == NULL || *env == NULL)
		return (NULL);
	return (*env + ft_strlen(name) + 1);
}
