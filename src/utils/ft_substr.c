#include "utils.h"

char	*ft_substr(const char *s, unsigned int start, size_t len);
static size_t	ft_strlcpy(char *dst, const char *src, size_t n);

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
    char	*substr;
    size_t	strlen;

    if (s == NULL)
        return (NULL);
    strlen = ft_strlen((char *)s);
    if (start > strlen)
        return (ft_strdup(""));
    if (strlen - start < len)
        len = strlen - start;
    substr = ft_calloc(len + 1, sizeof(char));
    if (substr == NULL)
        return (NULL);
    ft_strlcpy(substr, (s + start), (len + 1));
    return (substr);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
    const char	*s;

    s = src;
    if (n < 1)
        return (ft_strlen(src));
    while (*s && (n-- > 1))
        *dst++ = *s++;
    *dst = '\0';
    return (ft_strlen(src));
}
