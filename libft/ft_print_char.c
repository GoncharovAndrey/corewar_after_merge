/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:26:23 by bdudley           #+#    #+#             */
/*   Updated: 2019/04/30 17:54:27 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wcharlen(int c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else
		return (4);
}

void	ft_print_wchar(t_format *f, int c, int len)
{
	char wc[4];

	if (len == 1 || MB_CUR_MAX == 1)
		wc[0] = (char)c;
	else if ((len == 2 && MB_CUR_MAX > 2) || MB_CUR_MAX == 2)
	{
		wc[0] = (char)((c >> 6) | 0xC0);
		wc[1] = (char)((c & 0x3F) | 0x80);
	}
	else if ((len == 3 && MB_CUR_MAX > 3) || MB_CUR_MAX == 3)
	{
		wc[0] = (char)((c >> 12) | 0xE0);
		wc[1] = (char)(((c >> 6) & 0x3F) | 0x80);
		wc[2] = (char)((c & 0x3F) | 0x80);
	}
	else if ((len == 4 && MB_CUR_MAX > 4) || MB_CUR_MAX == 4)
	{
		wc[0] = (char)((c >> 18) | 0xF0);
		wc[1] = (char)(((c >> 12) & 0x3F) | 0x80);
		wc[2] = (char)(((c >> 6) & 0x3F) | 0x80);
		wc[3] = (char)((c & 0x3F) | 0x80);
	}
	ft_putbuffer(f, wc, len);
}

void	ft_print_char(char **str, t_format *f)
{
	int	padding;
	int	c;
	int	len;

	c = va_arg(f->ap, int);
	len = (**str == 'C' || f->length == LEN_L) ? ft_wcharlen(c) : 1;
	padding = ft_maxnum(f->min_width - len, 0);
	ft_putpad(padding, f, f->minus == 0);
	ft_print_wchar(f, c, len);
	ft_putpad(padding, f, f->minus == 1);
	*str += 1;
}
