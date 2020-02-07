/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_disasm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:29:16 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/30 16:29:20 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dis_asm.h"

int				main(int ac, char **av)
{
	t_data		*data;

	if (ac == 1)
		ft_error(NULL, 0);
	if (!(data = ft_memalloc(sizeof(t_data))))
		ft_error(NULL, ERROR_MALLOC);
	data->file = ft_create_file_name(av[1], data);
	ft_read_cor(data, av[1]);
	ft_dis_header(data);
	ft_dis_command(data);
	ft_putstr("Writing output program to ");
	ft_putendl(data->file);
	ft_del_data(&data);
	return (0);
}
