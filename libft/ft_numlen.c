/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:49:26 by jgoyette          #+#    #+#             */
/*   Updated: 2019/04/14 10:01:02 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(uintmax_t num, int base)
{
	int len;

	len = 1;
	while (num >= (uintmax_t)base)
	{
		num /= base;
		len += 1;
	}
	return (len);
}
