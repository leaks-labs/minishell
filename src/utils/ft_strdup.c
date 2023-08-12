/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:23:30 by shinfray          #+#    #+#             */
/*   Updated: 2023/08/12 15:32:26 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char		*ft_strdup(const char *s1);
static void	*ft_memcpy(void *dst, const void *src, size_t n);

char	*ft_strdup(const char *s1)
{
	const size_t	size = ft_strlen(s1);
	char			*s2;

	s2 = ft_calloc(size + 1, sizeof(*s2));
	if (s2 == NULL)
		return (NULL);
	return (ft_memcpy(s2, s1, size + 1));
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*cast_dst;
	const char	*cast_src;

	cast_dst = (char *)dst;
	cast_src = (const char *)src;
	if (n == 0 || cast_src == cast_dst)
		return (dst);
	while (n-- != 0)
		*cast_dst++ = *cast_src++;
	return (dst);
}
