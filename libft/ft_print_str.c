/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:36:05 by bdudley           #+#    #+#             */
/*   Updated: 2019/04/30 17:07:18 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wstrlen(wchar_t *str, int precision)
{
	int	wslen;
	int	wclen;

	wslen = 0;
	while (*str != L'\0')
	{
		wclen = ft_wcharlen(*str);
		if (precision != 0 && wslen + wclen > precision)
			return (wslen);
		wslen += wclen;
		str += 1;
	}
	return (wslen);
}

void	ft_print_wstr(char **str, t_format *f)
{
	wchar_t	*ptr;
	int		len;
	int		padding;
	int		wclen;

	if ((ptr = va_arg(f->ap, wchar_t *)) == NULL)
		ptr = L"(null)";
	len = ft_wstrlen(ptr, f->precision);
	padding = ft_maxnum(f->min_width - len, 0);
	ft_putpad(padding, f, f->minus == 0);
	while (*ptr && len >= (wclen = ft_wcharlen(*ptr)))
	{
		ft_print_wchar(f, *ptr, wclen);
		ptr += 1;
		len -= wclen;
	}
	ft_putpad(padding, f, f->minus == 1);
	*str += 1;
}

void	ft_print_str(char **str, t_format *f)
{
	char	*ptr;
	int		len;
	int		ptrlen;
	int		padding;

	if (**str == 'S' || f->length == LEN_L)
		ft_print_wstr(str, f);
	else
	{
		if ((ptr = va_arg(f->ap, char *)) == NULL)
			ptr = "(null)";
		ptrlen = ft_strlen(ptr);
		len = (f->precision == -1) ? 0 : ptrlen;
		len = (f->precision > 0 && f->precision <= ptrlen) ? f->precision : len;
		padding = ft_maxnum(f->min_width - len, 0);
		ft_putpad(padding, f, f->minus == 0);
		ft_putbuffer(f, ptr, len);
		ft_putpad(padding, f, f->minus == 1);
		*str += 1;
	}
}
