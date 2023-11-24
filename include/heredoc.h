/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:25 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:53:26 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "exec.h"

/*	HEREDOC	*/
int		ft_heredoc(t_msh *msh, t_cmd *cmd_list, t_exl *exl);
/*	RETRIEVE_HD_CONTENT	*/
char	*ft_get_hd_content(t_msh *msh, char *del, unsigned int *line_num);

#endif
