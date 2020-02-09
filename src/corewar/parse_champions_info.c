/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champions_info.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_champ					*parse_champ_information_from_file(t_champ *champion,
						int fd, int check_number_flag)
{
	unsigned char		map[4];

	champion->const_int = check_number_flag;
	champion->id = check_number_flag;
	read(fd, &map, 4);
	if (map[0] != 0 || map[1] != 234 || map[2] != 131 || map[3] != 243)
		error_print_exit("File has an invalid header");
	read_endl(128, fd, &champion->bot_name);
	read(fd, &map, 4);
	if (map[0] || map[1] || map[2] || map[3])
		error_print_exit("File has wrong NULL after folds");
	read(fd, &map, 4);
	champion->bot_size = from_memory_to_int(map, 0, 4);
	(champion->bot_size > CHAMP_MAX_SIZE || champion->bot_size == 0) ?
		error_print_exit("(max / min: 682 bytes / 1)") : 0;
	read_endl(2048, fd, &champion->bot_comment);
	read(fd, &map, 4);
	if (map[0] || map[1] || map[2] || map[3])
		error_print_exit("wrong NULL");
	return (champion);
}

long int				ft_pow(long int x, unsigned int n)
{
	long int			a;
	long int			p;

	a = x;
	p = 1;
	while (n > 0)
	{
		if ((n & 1) != 0)
			p *= a;
		a *= a;
		n >>= 1;
	}
	return (p);
}

void					get_arguments_from_byte(t_map *map, t_car *car)
{
	int					codage_octal;

	if (g_op[car->number_of_command].codage_octal)
	{
		codage_octal = map->map[get_index(car->i + 1)];
		if (g_op[car->number_of_command].argument_count >= 1)
			car->suite_of_arg[0] = ft_pow(2, (((codage_octal & 192) >> 6) - 1));
		if (g_op[car->number_of_command].argument_count >= 2)
			car->suite_of_arg[1] = ft_pow(2, (((codage_octal & 48) >> 4) - 1));
		if (g_op[car->number_of_command].argument_count >= 3)
			car->suite_of_arg[2] = ft_pow(2, (((codage_octal & 12) >> 2) - 1));
	}
	else
		car->suite_of_arg[0] = g_op[car->number_of_command].suite_of_arg[0];
}
