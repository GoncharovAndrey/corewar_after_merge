/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:53:01 by bdudley           #+#    #+#             */
/*   Updated: 2019/06/19 18:31:20 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_fractional(t_format *f, long double value)
{
	char	*fractional;
	int		counter;
	int		i;

	fractional = ft_strnew(f->precision + 1);
	if ((f->precision == -1 && f->hash == 1) || f->precision != -1)
		fractional[0] = '.';
	counter = 1;
	while (counter <= f->precision)
	{
		if (counter == f->precision &&
			((unsigned long long)(value * 100) % 10) > 4)
			value += 0.1;
		fractional[counter] = (unsigned long long)(value * 10) + '0';
		i = 0;
		while (fractional[counter - i] > 57)
		{
			fractional[counter - i] = '0';
			fractional[counter - ++i] += 1;
		}
		value = value * 10 - (unsigned long long)(value * 10);
		counter++;
	}
	return (fractional);
}

static char		*ft_put_double(long double value, t_format *f)
{
	char	*str;
	char	*integer;
	char	*fractional;

	value = value > 0 ? value : -value;
	integer = ft_ulltoa_base((unsigned long long)value, 10, 'a');
	value -= (unsigned long long)value;
	fractional = ft_fractional(f, value);
	str = ft_strnew(ft_strlen(integer) + ft_strlen(fractional));
	ft_strcpy(str, integer);
	ft_strcpy(str + ft_strlen(integer), fractional);
	free(integer);
	free(fractional);
	return (str);
}

static char		*ft_min_width(t_format *f,
				unsigned int counter, long double value)
{
	char		*s;

	s = ft_strnew(f->min_width - counter);
	if (f->zero == 0)
		s = (char *)ft_memset((void *)s, ' ', f->min_width - counter);
	else
	{
		if (f->space == 1 && f->plus == 0 && value >= 0)
		{
			ft_putbuffer(f, " ", 1);
			counter++;
		}
		s = (char *)ft_memset((void *)s, '0', f->min_width - counter);
		if (value >= 0 && f->plus == 1)
			ft_putbuffer(f, "+", 1);
		else if (value < 0)
			ft_putbuffer(f, "-", 1);
	}
	if (f->minus != 1)
	{
		ft_putbuffer(f, s, ft_strlen(s));
		free(s);
		s = NULL;
	}
	return (s);
}

static void		ft_sign(long double value, t_format *f, unsigned int counter)
{
	if (value >= 0 && f->plus == 1 && (f->zero == 0 || counter >= f->min_width))
		ft_putbuffer(f, "+", 1);
	else if (value < 0 && (f->zero == 0 || counter >= f->min_width))
		ft_putbuffer(f, "-", 1);
}

void			ft_print_double(char **str, t_format *f)
{
	long double		value;
	unsigned int	counter;
	char			*ptr;
	char			*s;

	s = NULL;
	f->precision = (f->precision == 0) ? 6 : f->precision;
	value = (f->length == 7) ? va_arg(f->ap, long double)
			: va_arg(f->ap, double);
	ptr = ft_put_double(value, f);
	counter = ((value >= 0 && f->plus == 1) || value < 0)
		? ft_strlen(ptr) + 1 : ft_strlen(ptr);
	if (counter < f->min_width)
		s = ft_min_width(f, counter, value);
	else if (f->space == 1 && f->plus == 0 && value >= 0)
		ft_putbuffer(f, " ", 1);
	ft_sign(value, f, counter);
	ft_putbuffer(f, ptr, ft_strlen(ptr));
	if (f->minus == 1 && s)
	{
		ft_putbuffer(f, s, ft_strlen(s));
		free(s);
	}
	*str += 1;
}
