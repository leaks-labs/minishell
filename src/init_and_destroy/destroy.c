#include "minishell.h"

int ft_quit(t_msh *msh)
{
    int exit_cpy;

    exit_cpy = msh->exit_status;
    ft_freef("%P, %p", msh->env, msh);
    return (exit_cpy);
}
