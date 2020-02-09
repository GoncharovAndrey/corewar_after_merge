/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				zjmp(t_car *car, t_map *map)
{
	int			index;

	car->distance_from_command += 1;
	index = get_value_from_argument(map, car, 1, CUT_MDX);
	if (car->carry)
	{
		car->i = get_index(car->i + (index % IDX_MOD));
		car->distance_from_command = 0;
	}
	return (0);
}
