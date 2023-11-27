/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:54:00 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/25 12:47:05 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "exec.h"

void		*ft_calloc(size_t count, size_t size);
char		**ft_dptrcpy(const char **dptr);
size_t		ft_dptrlen(const char **dptr);
void		*ft_freef(const char *formats, ...);
char		*ft_getenv(const char *name, const t_list *env);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isspace(int c);
char		*ft_join(int argc, ...);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		ft_putendl_fd(const char *s, int fd);
void		ft_putstr_fd(const char *s, int fd);
void		ft_rm_quotes(char *del);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strndup(const char *s1, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
intmax_t	ft_strtoimax(const char *str, bool *error);
char		*ft_substr(const char *s, unsigned int start, size_t len);
void		ft_uimaxtostr(char *str, size_t len, uintmax_t n);

#endif
