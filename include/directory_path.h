/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_path.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:11 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:53:12 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTORY_PATH_H
# define DIRECTORY_PATH_H

# include <stdbool.h>

/*	CHECK_DIR_PATH	*/
bool	ft_absolute_path_is_valid(const char *curpath, const char *initial_arg);
bool	ft_isadir(const char *path);
bool	ft_begin_with_dots(char *curpath);
/*	MOD_DIR_PATH	*/
char	*ft_cat_pwd_and_curpath(char *pwd, char *curpath);
void	ft_canonicalize(char *path);

#endif
