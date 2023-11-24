/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:49 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:53:50 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# define TMP_FILE_BASE_NAME "/tmp/msh-thd-"
# define MAX_LEN_NUM 20

# include "exec.h"

/*	ADAPT_REDIRECTIONS	*/
int		ft_set_input(t_exl *exl, const char *file);
int		ft_set_heredoc(t_exl *exl, const char *file);
int		ft_set_output(t_exl *exl, const char *file);
int		ft_set_append(t_exl *exl, const char *file);
/*	FILL_TMP	*/
int		ft_fill_tmp_pipe(const char *content);
int		ft_fill_tmp_file(const char *content);
/*	PIPES_CREATE_CLOSE	*/
int		ft_createpipe(int *pp);
void	ft_close_used_pipes(t_fd_io *fd_io);
/*	REDIRECTIONS	*/
int		ft_default_redirections(t_exl *exl);
int		ft_set_redirections(t_exl *exl, t_cmd *cmd);
int		ft_apply_redirections(t_exl *exl);
bool	ft_islastcmd(t_exl *exl);

#endif
