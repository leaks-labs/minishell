#include "minishell.h"

t_msh *ft_struct_init(char **envp);

t_msh *ft_struct_init(char **envp)
{
    t_msh *msh;

    msh = ft_calloc(1, sizeof(t_msh));
    if (msh == NULL)
        return (NULL);
    msh->env = ft_dptrcpy(envp);
    if (msh->env == NULL)
        return (ft_freef("%p", msh));
    return (msh);
}