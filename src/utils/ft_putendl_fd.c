#include "utils.h"
#include <unistd.h>

void	ft_putendl_fd(const char *s, int fd);

void	ft_putendl_fd(const char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}