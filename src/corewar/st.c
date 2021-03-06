/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				st(t_car *car, t_map *map)
{
	int			reg_one;
	int			reg_two;

	car->distance_from_command += 2;
	reg_one = get_value_from_argument(map, car, 1, GET_BYTE);
	reg_one = car->arr_reg[reg_one - 1];
	if (car->suite_of_arg[1] == T_REG)
	{
		reg_two = get_value_from_argument(map, car, 1, GET_BYTE);
		car->arr_reg[reg_two - 1] = reg_one;
	}
	else
	{
		reg_two = from_memory_to_int(map->map,
				car->i + car->distance_from_command, IND_SIZE);
		put_from_int_to_map(map->map, car->i + (reg_two % IDX_MOD),
				reg_one, DIR_SIZE);
		write_map_color(map, (car->i + (reg_two % IDX_MOD)), 4, car);
		car->distance_from_command += IND_SIZE;
	}
	return (0);
}
