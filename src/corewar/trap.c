/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		trap(t_car *car, t_map *map)
{
	int	reg_one;
	int	i;

	i = car->distance_from_command;
	car->distance_from_command += 1;
	reg_one = get_value_from_argument(map, car, 1, NO_CUT);
	if (car->arr_reg[1] != reg_one)
		car->distance_from_command = i;
	return (1);
}
