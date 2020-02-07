/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:14:05 by bdudley           #+#    #+#             */
/*   Updated: 2019/04/30 17:03:36 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putbuffer(t_format *f, char *str, int size)
{
	if (BUFF_SIZE - f->buffer_size < (unsigned int)size)
	{
		write(f->fd, f->buffer, f->buffer_size);
		write(f->fd, str, size);
		f->printed += f->buffer_size + size;
		f->size = 0;
		f->buffer_size = 0;
	}
	else
	{
		ft_memcpy(&(f->buffer[f->buffer_size]), str, size);
		f->buffer_size += size;
		f->size += size;
	}
}

void	ft_putpad(int nchars, t_format *f, int pad_needed)
{
	char	c;
	int		i;
	char	padding[nchars];

	if (pad_needed)
	{
		c = (f->zero == 1 && f->minus == 0) ? '0' : ' ';
		i = 0;
		while (i < nchars)
		{
			padding[i] = c;
			i += 1;
		}
		ft_putbuffer(f, padding, nchars);
	}
}

void	ft_putsign(intmax_t num, t_format *f)
{
	if (num < 0)
		ft_putbuffer(f, "-", 1);
	else if (f->plus == 1)
		ft_putbuffer(f, "+", 1);
	else if (f->space == 1)
		ft_putbuffer(f, " ", 1);
}

void	ft_putzeros(t_format *f, int nzeros)
{
	int		i;
	char	zeros[nzeros];

	i = 0;
	while (i < nzeros)
	{
		zeros[i] = '0';
		i += 1;
	}
	ft_putbuffer(f, zeros, nzeros);
}

void	ft_no_format_spec(char **str, t_format *f)
{
	int padding;

	padding = ft_maxnum(f->min_width - 1, 0);
	ft_putpad(padding, f, f->minus == 0);
	ft_putbuffer(f, *str, 1);
	ft_putpad(padding, f, f->minus == 1);
	*str += 1;
}
