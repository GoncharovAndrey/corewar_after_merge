/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:17:51 by jgoyette          #+#    #+#             */
/*   Updated: 2020/01/31 18:17:53 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_dprintf(int fd, const char *format, ...)
{
	char		*str;
	t_format	f;

	ft_init_format(&f, fd);
	str = (char *)format;
	va_start(f.ap, format);
	if (str == NULL)
		return (-1);
	while (str != NULL)
	{
		ft_clear_format(&f);
		if (*str == '%')
			ft_print_format(&str, &f);
		else
			ft_print_until(&str, &f);
	}
	write(f.fd, f.buffer, f.size);
	va_end(f.ap);
	return (f.size + f.printed);
}
