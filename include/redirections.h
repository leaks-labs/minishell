#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "exec.h"
# include <stdbool.h>

/*	ADAPT_REDIRECTIONS	*/
int				ft_set_input(t_exl *exl, char *file);
int				ft_set_heredoc(t_exl *exl, char *file);
int				ft_set_output(t_exl *exl, char *file);
int				ft_set_append(t_exl *exl, char *file);
/*	PIPES_CREATE_CLOSE	*/
int				ft_createpipe(int *pp);
void			ft_close_used_pipes(t_fd_io *fd_io);
/*	REDIRECTIONS	*/
int				ft_set_redirections(t_exl *exl, t_cmd *cmd);
uint8_t			ft_apply_redirections(t_exl *exl);

#endif