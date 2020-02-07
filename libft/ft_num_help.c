/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:12:45 by bdudley           #+#    #+#             */
/*   Updated: 2019/04/20 19:12:48 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_update_optionals(char id, t_format *f)
{
	if (f->precision != 0)
		f->zero = 0;
	if (id == 'O' || id == 'U' || id == 'D' || id == 'B')
		f->length = LEN_L;
	if (f->zero && (id == 'd' || id == 'D' || id == 'i'))
		f->precision = f->min_width;
}
