/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 11:55:23 by bdudley           #+#    #+#             */
/*   Updated: 2019/04/30 17:12:14 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_until_percent(char **str, t_format *f)
{
	char	*ptr;
	int		str_len;

	ptr = ft_strchr(*str, '%');
	if (ptr == NULL)
	{
		str_len = ft_strlen(*str);
		ft_putbuffer(f, *str, str_len);
	}
	else
	{
		str_len = ptr - *str;
		ft_putbuffer(f, *str, str_len);
	}
	*str = ptr;
}

void	ft_print_until(char **str, t_format *f)
{
	char	*percent_ptr;
	char	*brace_ptr;

	percent_ptr = ft_strchr(*str, '%');
	brace_ptr = ft_strchr(*str, '{');
	if ((brace_ptr < percent_ptr) || (percent_ptr == 0 && brace_ptr != 0))
		ft_putcolor(str, f);
	else
		ft_print_until_percent(str, f);
}

void	ft_call_type_print(char **str, t_format *f)
{
	if (**str == 'c' || **str == 'C')
		ft_print_char(str, f);
	else if (**str == 's' || **str == 'S')
		ft_print_str(str, f);
	else if (**str == 'p')
		ft_print_pointer(str, f);
	else if (**str == 'f' || **str == 'F')
		ft_print_double(str, f);
	else if (**str == 'b' || **str == 'B')
		ft_print_binary(str, f);
	else if (**str == 'd' || **str == 'D' || **str == 'i')
		ft_print_integer(str, f);
	else if (**str == 'o' || **str == 'O')
		ft_print_octal(str, f);
	else if (**str == 'x' || **str == 'X')
		ft_print_hex(str, f);
	else if (**str == 'u' || **str == 'U')
		ft_print_unsigned(str, f);
	else
		ft_no_format_spec(str, f);
}

void	ft_print_format(char **str, t_format *f)
{
	*str += 1;
	if (**str)
	{
		ft_handle_optionals(str, f);
		if (ft_isalpha(**str) || **str == '%')
			ft_call_type_print(str, f);
	}
}

int		ft_printf(const char *format, ...)
{
	char		*str;
	t_format	f;

	ft_init_format(&f, STDOUT_FILENO);
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
