/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimaxtostr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leex-labs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:17 by Leex-Labs         #+#    #+#             */
/*   Updated: 2023/11/24 14:58:18 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void			ft_uimaxtostr(char *str, size_t len, uintmax_t n);
static size_t	ft_count_digit(uintmax_t n);
static void		ft_fill(char *buf, size_t len, uintmax_t n, size_t i);

void	ft_uimaxtostr(char *buf, size_t len, uintmax_t n)
{
	size_t	numb_digit;

	if (len == 0)
		return ;
	numb_digit = ft_count_digit(n);
	if (len > 1)
		ft_fill(buf, len, n, numb_digit - 1);
	if (numb_digit >= len)
		numb_digit = len - 1;
	buf[numb_digit] = '\0';
}

static size_t	ft_count_digit(uintmax_t n)
{
	size_t	count;

	count = 1;
	while (n / 10 != 0)
	{
		++count;
		n /= 10;
	}
	return (count);
}

static void	ft_fill(char *buf, size_t len, uintmax_t n, size_t i)
{
	if (n > 9)
		ft_fill(buf, len, n / 10, i - 1);
	if (i < len - 1)
		buf[i] = n % 10 + '0';
}
