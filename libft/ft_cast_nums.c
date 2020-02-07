/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_nums.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:07:55 by bdudley           #+#    #+#             */
/*   Updated: 2019/04/26 16:17:46 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ft_cast_int(t_format *f)
{
	intmax_t	result;

	if (f->length == LEN_H)
		result = (intmax_t)((short)va_arg(f->ap, int));
	else if (f->length == LEN_HH)
		result = (intmax_t)((char)va_arg(f->ap, int));
	else if (f->length == LEN_L)
		result = (intmax_t)va_arg(f->ap, long);
	else if (f->length == LEN_LL)
		result = (intmax_t)va_arg(f->ap, long long);
	else if (f->length == LEN_J)
		result = va_arg(f->ap, intmax_t);
	else if (f->length == LEN_Z)
		result = (intmax_t)va_arg(f->ap, size_t);
	else
		result = (intmax_t)va_arg(f->ap, int);
	return (result);
}

uintmax_t	ft_cast_uint(t_format *f)
{
	uintmax_t	result;

	if (f->length == LEN_H)
		result = (uintmax_t)((unsigned short)va_arg(f->ap, int));
	else if (f->length == LEN_HH)
		result = (uintmax_t)((unsigned char)va_arg(f->ap, int));
	else if (f->length == LEN_L)
		result = (uintmax_t)va_arg(f->ap, unsigned long);
	else if (f->length == LEN_LL)
		result = (uintmax_t)va_arg(f->ap, unsigned long long);
	else if (f->length == LEN_J)
		result = va_arg(f->ap, uintmax_t);
	else if (f->length == LEN_Z)
		result = (uintmax_t)va_arg(f->ap, size_t);
	else
		result = (uintmax_t)va_arg(f->ap, unsigned int);
	return (result);
}
