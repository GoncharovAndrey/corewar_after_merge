/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:07:07 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/04 17:47:48 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_is_register(const char *str)
{
	int len;

	if (*str != 'r')
		return (0);
	str += 1;
	while (*str == '0')
		str += 1;
	len = ft_strlen(str);
	if (len < 1 || len > 2)
		return (0);
	if (*str < '1' || *str > '9')
		return (0);
	str += 1;
	if (len == 2 && (*str < '0' || *str > '9'))
		return (0);
	return (1);
}

int		ft_is_whitespace(int c)
{
	return (c == ' ' || c == '\t'
		|| (c == '\v' || c == '\f' || c == '\r'));
}

void	ft_add_token(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	if (tokens && new_token)
	{
		tmp = *tokens;
		if (tmp)
		{
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = new_token;
		}
		else
			*tokens = new_token;
	}
}
