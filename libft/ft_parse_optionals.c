/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 19:38:35 by jgoyette          #+#    #+#             */
/*   Updated: 2019/05/18 18:08:05 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_flags(char **str, t_format *f)
{
	while (**str)
	{
		if (**str == '#')
			f->hash = 1;
		else if (**str == '0')
			f->zero = 1;
		else if (**str == '-')
			f->minus = 1;
		else if (**str == '+')
			f->plus = 1;
		else if (**str == ' ')
			f->space = 1;
		else
			break ;
		*str += 1;
	}
	if (f->minus)
		f->zero = 0;
	if (f->plus)
		f->space = 0;
}

void	ft_parse_width(char **str, t_format *f)
{
	int width;

	if ((width = ft_atoi(*str)) > 0 || **str == '*')
	{
		if (**str == '*')
		{
			if ((width = va_arg(f->ap, int)) < 0)
				f->minus = 1;
			f->min_width = (width < 0 ? -width : width);
			width = 1;
		}
		else
			f->min_width = width;
		*str += ft_numlen((unsigned int)width, (unsigned int)10);
	}
}

void	ft_parse_precision(char **str, t_format *f)
{
	int precision;

	while (**str == '.')
	{
		*str += 1;
		if ((precision = ft_atoi(*str)) > 0 || **str == '*')
		{
			if (**str == '*')
			{
				precision = va_arg(f->ap, int);
				f->precision = (precision == 0) ? -1 : precision;
				f->precision = (precision < 0) ? 0 : f->precision;
				precision = 1;
			}
			else
				f->precision = precision;
			*str += ft_numlen((unsigned int)precision, (unsigned int)10);
		}
		else
		{
			f->precision = -1;
			while (ft_isdigit(**str))
				*str += 1;
		}
	}
}

void	ft_put_length(char **str, t_format *f, unsigned int len_type, int size)
{
	f->length = len_type;
	*str += size;
}

void	ft_parse_length(char **str, t_format *f)
{
	while (**str)
	{
		if (**str == 'h' && *(*str + 1) == 'h')
			ft_put_length(str, f, LEN_HH, 2);
		else if (**str == 'h')
			ft_put_length(str, f, LEN_H, 1);
		else if (**str == 'l' && *(*str + 1) == 'l')
			ft_put_length(str, f, LEN_LL, 2);
		else if (**str == 'l')
			ft_put_length(str, f, LEN_L, 1);
		else if (**str == 'j')
			ft_put_length(str, f, LEN_J, 1);
		else if (**str == 'z')
			ft_put_length(str, f, LEN_Z, 1);
		else if (**str == 'L')
			ft_put_length(str, f, LEN_LD, 1);
		else
			break ;
	}
}
