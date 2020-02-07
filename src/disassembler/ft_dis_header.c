/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dis_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:32:07 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/30 16:32:08 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_op.h"
#include "dis_asm.h"

unsigned int		ft_read_number(unsigned char *str, unsigned short int byte)
{
	unsigned int	res;
	int				i;

	res = 0;
	i = 0;
	if (byte > 4 || !str)
		return (0);
	while (i < byte)
	{
		res |= *(str + i) << (8 * (byte - i - 1));
		i++;
	}
	return (res);
}

void				ft_dis_header(t_data *data)
{
	if (ft_read_number(data->name, 4) != COREWAR_EXEC_MAGIC)
		ft_error(data, ERROR_BIN);
	ft_putstr_fd(NAME_CMD_STRING, data->fd[1]);
	write(data->fd[1], " \"", 2);
	write(data->fd[1], data->name + 4, ft_strlen((char *)(data->name + 4)));
	write(data->fd[1], "\"\n", 2);
	ft_putstr_fd(COMMENT_CMD_STRING, data->fd[1]);
	write(data->fd[1], " \"", 2);
	write(data->fd[1], data->name + 140, ft_strlen((char *)(data->name + 140)));
	write(data->fd[1], "\"\n\n", 3);
}
