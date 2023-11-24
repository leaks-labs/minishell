/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freef.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:57:10 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:57:12 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdarg.h>
#include <stdlib.h>

void	*ft_freef(const char *formats, ...);

void	*ft_freef(const char *formats, ...)
{
	va_list	ap;
	size_t	i;
	void	**dptr;

	va_start(ap, formats);
	while (*formats != '\0')
	{
		if (*formats == '%')
		{
			++formats;
			if (*formats == 'p')
				free(va_arg(ap, void *));
			else if (*formats == 'P')
			{
				dptr = va_arg(ap, void **);
				i = 0;
				while (dptr != NULL && dptr[i] != NULL)
					free(dptr[i++]);
				free(dptr);
			}
		}
		++formats;
	}
	va_end(ap);
	return (NULL);
}
