/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:46 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/25 01:44:55 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "exec.h"

/*	GET_CMD_PATH	*/
char		*ft_get_cmd_path(t_list_node *path, const char *cmd);
bool		ft_isapath(const char *str);
/*	GET_PATH	*/
t_list_node	*ft_get_path(t_list *env);
size_t		ft_path_token_len(const char *str);
t_list_node	*ft_append_token(t_list_node *path_token_list, char *value);

#endif
