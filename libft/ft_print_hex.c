/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 18:14:11 by bdudley           #+#    #+#             */
/*   Updated: 2019/04/30 16:40:08 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_calc_len(t_format *f, uintmax_t num, int numlen)
{
	unsigned int	len;

	if (f->precision == -1 && num == 0)
		len = 0;
	else if (f->precision > numlen)
		len = f->precision;
	else
		len = numlen;
	if (f->hash && num > 0)
		len += 2;
	if (f->zero && f->min_width > len)
		len = f->min_width;
	return (len);
}

void		ft_print_hex(char **str, t_format *f)
{
	uintmax_t	num;
	char		*ptr;
	int			ptrlen;
	int			len;
	int			padding;

	ft_update_optionals(**str, f);
	num = ft_cast_uint(f);
	ptr = ft_ulltoa_base(num, 16, (**str == 'x') ? 'a' : 'A');
	ptrlen = (num != 0 || f->precision != -1) ? ft_strlen(ptr) : 0;
	len = ft_calc_len(f, num, ptrlen);
	padding = ft_maxnum(f->min_width - len, 0);
	ft_putpad(padding, f, f->minus == 0);
	if (f->hash && num > 0)
		(**str == 'x') ? ft_putbuffer(f, "0x", 2) : ft_putbuffer(f, "0X", 2);
	ft_putzeros(f, ft_maxnum(len - ptrlen - ((f->hash && num > 0) ? 2 : 0), 0));
	ft_putbuffer(f, ptr, ptrlen);
	ft_putpad(padding, f, f->minus == 1);
	*str += 1;
	free(ptr);
}
