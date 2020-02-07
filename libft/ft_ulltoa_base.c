/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:03:40 by bdudley           #+#    #+#             */
/*   Updated: 2019/04/20 19:04:28 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_getchar(int num, char letter_case)
{
	if (num < 10)
		return (num + '0');
	else
		return (num - 10 + letter_case);
}

char		*ft_ulltoa_base(uintmax_t num, int base, char letter_case)
{
	char	*result;
	int		len;

	len = ft_numlen(num, base);
	if ((result = ft_strnew(len)))
	{
		while (len > 0)
		{
			result[len - 1] = ft_getchar(num % base, letter_case);
			num /= base;
			len -= 1;
		}
	}
	return (result);
}
