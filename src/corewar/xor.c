/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				xor(t_car *car, t_map *map)
{
	int			reg_one;
	int			reg_two;
	int			reg_three;

	car->distance_from_command += 2;
	reg_one = get_value_from_argument(map, car, 1, CUT_MDX);
	reg_two = get_value_from_argument(map, car, 2, CUT_MDX);
	reg_three = map->map[get_index(
			car->i + car->distance_from_command)];
	car->arr_reg[reg_three - 1] = reg_one ^ reg_two;
	car->carry = (!car->arr_reg[reg_three - 1]) ? 1 : 0;
	car->distance_from_command += 1;
	return (0);
}
