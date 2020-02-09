/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_to_put_take_from_memory.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					get_register_from_byte(t_map *map, t_car *car)
{
	int				value;

	value = map->map[get_index(car->i + car->distance_from_command)];
	car->distance_from_command += 1;
	return (value);
}

int					get_value_from_argument(t_map *map, t_car *car,
					int index, int action)
{
	int				value;

	value = 0;
	if (action == GET_BYTE)
		return (get_register_from_byte(map, car));
	else if (car->suite_of_arg[index - 1] == T_REG)
	{
		value = map->map[get_index(car->i + car->distance_from_command)];
		value = car->arr_reg[value - 1];
	}
	else if (car->suite_of_arg[index - 1] == T_DIR)
		value = from_memory_to_int(map->map,
				car->i + car->distance_from_command,
		g_op[car->number_of_command].label);
	else if (car->suite_of_arg[index - 1] == T_IND)
	{
		value = from_memory_to_int(map->map,
				car->i + car->distance_from_command, IND_SIZE);
		value = action ? (value % IDX_MOD) : value;
		value = from_memory_to_int(map->map, car->i + value, DIR_SIZE);
	}
	car->distance_from_command += distanse_length(
			car->suite_of_arg[index - 1], g_op[car->number_of_command].label);
	return (value);
}

void				put_from_int_to_map(unsigned char *map, int index,
										int value, int label)
{
	int				i;

	i = 0;
	while (label)
	{
		map[get_index(index + label - 1)] = (value >> i);
		i += 8;
		label--;
	}
}

int					from_memory_to_int(unsigned char *map, int addr, int label)
{
	int				result;
	int				sign;
	int				i;

	result = 0;
	sign = (map[get_index(addr)] & 0x80);
	i = 0;
	while (label)
	{
		result += sign ? ((map[get_index(addr + label - 1)] ^ 0xFF) << (i * 8))
				: map[get_index(addr + label - 1)] << (i * 8);
		i++;
		label--;
	}
	(sign) ? result = ~(result) : 0;
	return (result);
}
