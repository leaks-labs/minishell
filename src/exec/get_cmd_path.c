#include "exec.h"

char		*ft_get_cmd_path(char **path, char *cmd);
bool	ft_isapath(char *str);
static char	*ft_check_one_path(char *cmd);
static char	*ft_search_in_path(char **path, char *cmd);

char	*ft_get_cmd_path(char **path, char *cmd)
{
	if (ft_isapath(cmd) == true)
		return (ft_check_one_path(cmd));
	else
		return (ft_search_in_path(path, cmd));
}

bool	ft_isapath(char *str)
{
	while (*str != '\0' && *str != '/')
		++str;
	return (*str == '/');
}

static char	*ft_check_one_path(char *cmd)
{
	char		*cmd_path;
	struct stat	buf;

	cmd_path = NULL;
	if (stat(cmd, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode) == true)
			errno = EISDIR;
		else
			cmd_path = ft_strdup(cmd);
	}
	return (cmd_path);
}

static char	*ft_search_in_path(char **path, char *cmd)
{
	char		*cmd_path;
	struct stat	buf;

	cmd_path = NULL;
	while (path != NULL && *path != NULL)
	{
		cmd_path = ft_join(2, *path, cmd);
		if (cmd_path == NULL)
				return (NULL);
		if (stat(cmd_path, &buf) == 0)
		{
			if (S_ISDIR(buf.st_mode) == true)
			{
				cmd_path = ft_freef("%p", cmd_path);
				errno = EISDIR;
			}
			break ;
		}
		cmd_path = ft_freef("%p", cmd_path);
		++path;
	}
	return (cmd_path);
}
