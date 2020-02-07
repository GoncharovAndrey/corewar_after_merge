/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 09:38:44 by jgoyette          #+#    #+#             */
/*   Updated: 2019/04/30 17:14:25 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_format(t_format *f, int fd)
{
	f->fd = fd;
	f->buffer_size = 0;
	f->size = 0;
	f->printed = 0;
}

void	ft_clear_format(t_format *f)
{
	f->length = 0;
	f->hash = 0;
	f->zero = 0;
	f->minus = 0;
	f->plus = 0;
	f->space = 0;
	f->min_width = 0;
	f->precision = 0;
}

void	ft_handle_optionals(char **str, t_format *f)
{
	ft_parse_flags(str, f);
	ft_parse_width(str, f);
	ft_parse_precision(str, f);
	ft_parse_length(str, f);
	ft_parse_flags(str, f);
}
