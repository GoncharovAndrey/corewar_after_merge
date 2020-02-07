/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:15:09 by jgoyette          #+#    #+#             */
/*   Updated: 2020/01/31 18:15:53 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char *str, int base)
{
	int	i;
	int nb;

	nb = 0;
	i = 0;
	while (ft_isalnum(str[i]))
	{
		nb = nb * base;
		if (str[i] >= 48 && str[i] <= 57)
		{
			nb = nb + (str[i] - 48);
		}
		else if (str[i] >= 97 && str[i] <= 122)
			nb = nb + (str[i] - 97 + 10);
		else if (str[i] >= 65 && str[i] <= 90)
			nb = nb + (str[i] - 65 + 10);
		i += 1;
	}
	return (nb);
}

int			ft_atoi_base(char *str, int base)
{
	int i;
	int sign;

	i = 0;
	sign = 1;
	while (ft_isspace((int)str[i]))
		i += 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (check(&str[i], base) * sign);
}
