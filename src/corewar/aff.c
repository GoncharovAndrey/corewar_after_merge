/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				aff(t_car *car, t_map *map)
{
	int			reg_one;

	car->distance_from_command += 2;
	car->suite_of_arg[0] = T_REG;
	reg_one = get_value_from_argument(map, car, 1, GET_BYTE);
	if (map->aff_flag)
		ft_printf("%c\n", reg_one % 256);
	return (0);
}
