/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_car				*copy_car(t_car *car, int value)
{
	t_car			*new;
	int				i;

	value = get_index(car->i + value);
	new = init_car(car->id, value);
	i = -1;
	while (++i < REG_NUMBER)
		new->arr_reg[i] = car->arr_reg[i];
	new->carry = car->carry;
	new->last_live = car->last_live;
	return (new);
}

int					ffork(t_car *car, t_map *map)
{
	int				reg_one;
	t_car			*new_car;

	car->distance_from_command += 1;
	reg_one = get_value_from_argument(map, car, 1, CUT_MDX);
	new_car = copy_car(car, reg_one % IDX_MOD);
	ft_lst_car_start(&map->start_car, new_car);
	return (1);
}
