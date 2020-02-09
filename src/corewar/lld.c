/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				lld(t_car *car, t_map *map)
{
	int			reg_one;
	int			reg_two;

	car->distance_from_command += 2;
	reg_one = get_value_from_argument(map, car, 1, NO_CUT);
	reg_two = get_value_from_argument(map, car, 1, GET_BYTE);
	car->carry = (!reg_one) ? 1 : 0;
	car->arr_reg[reg_two - 1] = reg_one;
	return (1);
}
