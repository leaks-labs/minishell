#include "init.h"
#include "utils.h"

t_msh			*ft_struct_init(char **envp);

t_msh	*ft_struct_init(char **envp)
{
	t_msh	*msh;

	msh = ft_calloc(1, sizeof(t_msh));
	if (msh == NULL)
		return (NULL);
	if (ft_env_to_list(&msh->env, envp) == -1)
		return (ft_freef("%p", msh));
	return (msh);
}
