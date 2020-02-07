/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:53:01 by bdudley           #+#    #+#             */
/*   Updated: 2019/04/30 17:08:32 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_calc_len(t_format *f, intmax_t num, int numlen)
{
	int len;

	if (f->precision == -1 && num == 0)
		len = 0;
	else if (f->precision > numlen)
		len = f->precision;
	else
		len = numlen;
	if (f->plus || f->space || num < 0)
		len += 1;
	return (len);
}

void		ft_print_integer(char **str, t_format *f)
{
	intmax_t	num;
	char		*ptr;
	int			ptrlen;
	int			len;
	int			padding;

	ft_update_optionals(**str, f);
	num = ft_cast_int(f);
	if ((f->plus || f->space || num < 0) && f->zero)
		f->precision -= (f->precision > 0) ? 1 : 0;
	ptr = ft_ulltoa_base((num < 0) ? -num : num, 10, 'a');
	ptrlen = (num != 0 || f->precision != -1) ? ft_strlen(ptr) : 0;
	len = ft_calc_len(f, num, ptrlen);
	padding = ft_maxnum(f->min_width - len, 0);
	ft_putpad(padding, f, f->minus == 0);
	ft_putsign(num, f);
	ft_putzeros(f, ft_maxnum(f->precision - ptrlen, 0));
	ft_putbuffer(f, ptr, ptrlen);
	ft_putpad(padding, f, f->minus == 1);
	*str += 1;
	free(ptr);
}
