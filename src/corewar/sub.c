/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				sub(t_car *car, t_map *map)
{
	int			reg_one;
	int			reg_two;
	int			reg_three;

	car->distance_from_command += 2;
	reg_one = get_value_from_argument(map, car, 1, GET_BYTE);
	reg_two = get_value_from_argument(map, car, 1, GET_BYTE);
	reg_one = car->arr_reg[reg_one - 1] - car->arr_reg[reg_two - 1];
	car->carry = (!reg_one) ? 1 : 0;
	reg_three = map->map[get_index(car->i + car->distance_from_command)];
	car->arr_reg[reg_three - 1] = reg_one;
	car->distance_from_command += 1;
	return (0);
}
