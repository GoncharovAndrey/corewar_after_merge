/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:58:27 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/30 16:58:29 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dis_asm.h"

void		ft_error(t_data *data, char *str)
{
	ft_putendl_fd(str, 2);
	if (data)
	{
		if (data->fd[1])
			ft_putendl_fd(str, data->fd[1]);
		ft_del_data(&data);
	}
	exit(EXIT_FAILURE);
}
