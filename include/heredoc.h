/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:25 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 21:58:20 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "exec.h"

/*	HEREDOC	*/
int		ft_heredoc(t_msh *msh, t_cmd *cmd_list, t_exl *exl);
/*	RETRIEVE_HD_CONTENT	*/
char	*ft_init_hd_content(char **hd_content);
char	*ft_retrieve_one_line(void);
bool	ft_end_of_hd(char *current_line, char *del, unsigned int line_num);
char	*ft_do_expansion(t_msh *msh, char *current_line, bool to_expand);
char	*ft_update_hd_content(char *hd_content, char *current_line);

#endif
