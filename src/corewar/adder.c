/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		error_print_exit(char *temp)
{
	ft_dprintf(2, "ERROR: ");
	ft_dprintf(2, "%s\n", temp);
	exit(-1);
}

void		read_endl(int size, int fd, char **str)
{
	int pos;

	pos = read(fd, *str, size);
	(*str)[pos] = '\0';
}

int			time_to_check_cycles(t_map *map)
{
	return (map->cycles_to_die == map->cycles_after_check
			|| map->cycles_to_die <= 0);
}

int			valid_parameters(int args)
{
	return (args >= 2);
}

int			get_index(int coord)
{
	coord %= MEM_SIZE;
	if (coord < 0)
		coord += MEM_SIZE;
	return (coord);
}
