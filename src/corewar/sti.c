/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					sti(t_car *car, t_map *map)
{
	int				reg_one;
	int				reg_two;
	int				reg_three;

	car->distance_from_command += 2;
	reg_one = get_value_from_argument(map, car, 1, GET_BYTE);
	reg_one = car->arr_reg[reg_one - 1];
	reg_two = get_value_from_argument(map, car, 2, CUT_MDX);
	reg_three = get_value_from_argument(map, car, 3, CUT_MDX);
	put_from_int_to_map(map->map,
			(car->i + ((reg_two + reg_three) % IDX_MOD)), reg_one, DIR_SIZE);
	write_map_color(map, (car->i + ((reg_two + reg_three) % IDX_MOD)),
			4, car);
	return (1);
}
