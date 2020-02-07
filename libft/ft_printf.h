/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 11:57:32 by bdudley           #+#    #+#             */
/*   Updated: 2019/04/30 17:18:04 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define BUFF_SIZE 4096
# define LEN_H		1
# define LEN_HH		2
# define LEN_L		3
# define LEN_LL		4
# define LEN_J		5
# define LEN_Z		6
# define LEN_LD		7

# define COLOR_EOC		"\033[0m"
# define COLOR_RED		"\033[31m"
# define COLOR_GREEN	"\033[32m"
# define COLOR_YELLOW	"\033[33m"
# define COLOR_BLUE		"\033[34m"
# define COLOR_MAGENTA	"\033[35m"
# define COLOR_CYAN		"\033[36m"

typedef struct		s_format
{
	int				fd;
	int				precision;
	unsigned int	min_width;
	unsigned int	size;
	unsigned int	printed;
	unsigned int	buffer_size;
	unsigned int	length : 3;
	unsigned int	hash : 1;
	unsigned int	zero : 1;
	unsigned int	minus : 1;
	unsigned int	plus : 1;
	unsigned int	space : 1;
	char			buffer[BUFF_SIZE];
	va_list			ap;
}					t_format;

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
void				ft_putbuffer(t_format *f, char *str, int size);
int					ft_printf(const char *format, ...);
void				ft_putpad(int nchars, t_format *f, int pad_needed);
void				ft_putprefix(uintmax_t num, char id, t_format *f);
void				ft_putsign(intmax_t num, t_format *f);
void				ft_putzeros(t_format *f, int nzeros);
void				ft_print_format(char **str, t_format *f);
void				ft_print_until(char **str, t_format *f);
void				ft_print_char(char **str, t_format *f);
void				ft_print_str(char **str, t_format *f);
void				ft_print_binary(char **str, t_format *f);
void				ft_print_integer(char **str, t_format *f);
void				ft_print_pointer(char **str, t_format *f);
void				ft_print_hex(char **str, t_format *f);
void				ft_print_octal(char **str, t_format *f);
void				ft_print_unsigned(char **str, t_format *f);
void				ft_print_double(char **str, t_format *f);
void				ft_no_format_spec(char **str, t_format *f);
void				ft_init_format(t_format *f, int fd);
void				ft_clear_format(t_format *f);
void				ft_handle_optionals(char **str, t_format *f);
void				ft_parse_flags(char **str, t_format *f);
void				ft_parse_width(char **str, t_format *f);
void				ft_parse_precision(char **str, t_format *f);
void				ft_parse_length(char **str, t_format *f);
void				ft_update_optionals(char format_id, t_format *f);
intmax_t			ft_cast_int(t_format *f);
uintmax_t			ft_cast_uint(t_format *f);
void				ft_print_wchar(t_format *f, int c, int len);
int					ft_wcharlen(int c);
void				ft_putcolor(char **str, t_format *f);

#endif
