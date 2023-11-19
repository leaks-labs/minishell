#include "utils.h"

void	ft_putendl_fd(const char *s, int fd);

void	ft_putendl_fd(const char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\n", fd);
}
