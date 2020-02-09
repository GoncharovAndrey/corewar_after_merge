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

int					live(t_car *car, t_map *map)
{
	int				reg_one;

	car->distance_from_command += 1;
	car->live += 1;
	map->all_lives += 1;
	car->last_live = map->cycles;
	reg_one = get_value_from_argument(map, car, 1, NO_CUT);
	if (reg_one < 0 && reg_one >= -map->car_numb)
		map->last_car = -reg_one;
	return (1);
}
