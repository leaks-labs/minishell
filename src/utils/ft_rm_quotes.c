/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:57:43 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:57:44 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_rm_quotes(char *del);

void	ft_rm_quotes(char *del)
{
	char	to_trim;
	size_t	i;
	size_t	j;

	to_trim = '\0';
	i = 0;
	j = i;
	while (del[i] != '\0')
	{
		if (to_trim == '\0' && (del[i] == '\"' || del[i] == '\''))
			to_trim = del[i];
		else if (to_trim != '\0' && del[i] == to_trim)
			to_trim = '\0';
		else
			del[j++] = del[i];
		++i;
	}
	del[j] = '\0';
}
