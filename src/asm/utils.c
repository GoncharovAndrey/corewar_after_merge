/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:44:28 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/04 17:47:24 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int	ft_atoui_max(char *str)
{
	unsigned long	result;
	unsigned long	tmp;
	int				sign;

	result = 0;
	tmp = 0;
	sign = 1;
	if (*str == '-')
	{
		str += 1;
		sign = -1;
	}
	while (*str >= '0' && *str <= '9' && tmp <= result)
	{
		tmp = result;
		result = result * 10 + (*str - '0');
		str += 1;
	}
	if (tmp > result)
		return ((unsigned int)((sign == 1) ? UINT_MAX : 0));
	else
		return ((unsigned int)(result * sign));
}

t_op			*ft_get_op(const char *name)
{
	int	i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strequ(g_op_tab[i].name, name))
			return (&g_op_tab[i]);
		i += 1;
	}
	return (NULL);
}

unsigned int	ft_get_insruction_line_size(t_token *token)
{
	unsigned int	size;

	size = token->size;
	token = token->next;
	while (token && token->type != INSTRUCTION)
	{
		size += token->size;
		token = token->next;
	}
	return (size);
}
