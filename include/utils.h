#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdarg.h>

char	*ft_getenv(const char *name, char **env);
void	*ft_calloc(size_t count, size_t size);
char	**ft_dptrcpy(char **dptr);
size_t	ft_dptrlen(char	**dptr);
void	*ft_freef(const char *formats, ...);
char	*ft_join(int argc, ...);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif
