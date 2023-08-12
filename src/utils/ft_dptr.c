#include "utils.h"

char	**ft_dptrcpy(char **dptr);
static size_t	ft_dptrlen(char	**dptr);

char	**ft_dptrcpy(char **dptr)
{
    char	**dptr_cpy;
    size_t	i;

    if (dptr == NULL || *dptr == NULL)
        return (NULL);
    dptr_cpy = ft_calloc(ft_dptrlen(dptr) + 1, sizeof(char *));
    if (dptr_cpy == NULL)
        return (NULL);
    i = 0;
    while (dptr[i] != NULL)
    {
        dptr_cpy[i] = ft_strdup(dptr[i]);
        if (dptr_cpy[i] == NULL)
            return (ft_freef("%P", dptr_cpy));
        ++i;
    }
    return (dptr_cpy);
}

static size_t	ft_dptrlen(char	**dptr)
{
    size_t	i;

    i = 0;
    while (dptr[i] != NULL)
        ++i;
    return (i);
}