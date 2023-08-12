#include "utils.h"

char	**ft_split(char const *s, char c);
static size_t	ft_cntw(char const *str, const char sep);
static char	**ft_mkw(const char *str, const char sep, char **tab, size_t cntw);

char	**ft_split(char const *s, char c)
{
    char	**tab;
    size_t	cntw;

    if (!s)
        return (NULL);
    cntw = ft_cntw(s, c);
    tab = malloc(sizeof(*tab) * (cntw + 1));
    if (!tab)
        return (NULL);
    tab = ft_mkw(s, c, tab, cntw);
    if (tab)
        tab[cntw] = 0;
    return (tab);
}

static size_t	ft_cntw(char const *str, const char sep)
{
    size_t	cntw;

    cntw = 0;
    while (*str)
    {
        if (*str == sep)
            ++str;
        else
        {
            ++cntw;
            while (*str && *str != sep)
                ++str;
        }
    }
    return (cntw);
}

static char	**ft_mkw(const char *str, const char sep, char **tab, size_t cntw)
{
    char	**cpytab;
    size_t	len;

    cpytab = tab;
    while (cntw--)
    {
        while (*str && *str == sep)
            ++str;
        len = 0;
        while (str[len] && str[len] != sep)
            ++len;
        *tab = ft_substr(str, 0, len);
        str += len;
        if (!(*tab))
        {
            ft_free("%P", cpytab);
            return (NULL);
        }
        ++tab;
    }
    return (cpytab);
}