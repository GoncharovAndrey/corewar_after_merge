/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					lfork(t_car *car, t_map *map)
{
	int				reg_one;
	t_car			*new_car;

	car->distance_from_command += 1;
	reg_one = get_value_from_argument(map, car, 1, CUT_MDX);
	new_car = copy_car(car, reg_one);
	ft_lst_car_start(&map->start_car, new_car);
	return (1);
}
