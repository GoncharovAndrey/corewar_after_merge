/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 18:44:57 by jgoyette          #+#    #+#             */
/*   Updated: 2019/04/20 19:03:26 by bdudley          ###   ########.fr       */
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

char		*ft_lltoa_base(intmax_t value, int base, char letter_case)
{
	int			sign;
	uintmax_t	num;
	char		*result;
	int			len;

	sign = (value < 0 && base == 10) ? 1 : 0;
	num = (value < 0) ? -value : value;
	len = ft_numlen(num, base) + sign;
	if ((result = ft_strnew(len)))
	{
		while (len > 0)
		{
			result[len - 1] = ft_getchar(num % base, letter_case);
			num /= base;
			len -= 1;
		}
		if (sign)
			result[0] = '-';
	}
	return (result);
}
