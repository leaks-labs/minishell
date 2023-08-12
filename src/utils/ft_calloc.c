/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:15:39 by shinfray          #+#    #+#             */
/*   Updated: 2023/08/12 15:32:12 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void		*ft_calloc(size_t count, size_t size);
static void	*ft_memset(void *b, int c, size_t len);

void	*ft_calloc(size_t count, size_t size)
{
	const size_t	f_size = size * count;
	void			*ptr;

	ptr = malloc(f_size);
	if (ptr != NULL)
		ft_memset(ptr, 0, f_size);
	return (ptr);
}

static void	*ft_memset(void *b, int c, size_t len)
{
	const unsigned char	uc_c = (const unsigned char)c;
	unsigned char		*uc_b;

	uc_b = (unsigned char *)b;
	while (len-- != 0)
		*uc_b++ = uc_c;
	return (b);
}