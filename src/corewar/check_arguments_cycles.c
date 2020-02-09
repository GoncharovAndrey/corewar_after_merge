/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments_cycles.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			check_cycle_and_substruct(t_car *car, t_map *map)
{
	if (car->cycle_to_operation == 0)
	{
		car->number_of_command = map->map[car->i];
		if ((int)map->map[car->i] >= 1 && (int)map->map[car->i] <=
		(16 + map->add_operation))
			car->cycle_to_operation = g_op[car->number_of_command].cycles;
	}
	(car->cycle_to_operation > 0) ? car->cycle_to_operation -= 1 : 0;
	if (car->cycle_to_operation == 0)
		return (1);
	return (0);
}

int			check_valid_argumemts_and_reg(t_car *car, t_map *map)
{
	int		i;
	int		distance_from_command;
	int		reg;

	i = -1;
	while (++i < g_op[car->number_of_command].argument_count)
		if (!(car->suite_of_arg[i] &
			g_op[car->number_of_command].suite_of_arg[i]))
			return (0);
	i = -1;
	distance_from_command = g_op[car->number_of_command].codage_octal ? 2 : 1;
	while (++i < g_op[car->number_of_command].argument_count)
	{
		reg = map->map[get_index(car->i + distance_from_command)];
		if ((car->suite_of_arg[i] == T_REG) && (reg < 1 || reg > 16))
			return (0);
		distance_from_command += distanse_length(car->suite_of_arg[i],
				g_op[car->number_of_command].label);
	}
	return (1);
}

int			distance_to_next_command(t_car *car)
{
	int		i;
	int		distance_from_command;

	i = -1;
	distance_from_command = g_op[car->number_of_command].codage_octal ? 2 : 1;
	while (++i < g_op[car->number_of_command].argument_count)
		distance_from_command += distanse_length(car->suite_of_arg[i],
				g_op[car->number_of_command].label);
	return (distance_from_command);
}

int			distanse_length(int arg_type, int label)
{
	if (arg_type == T_REG)
		return (1);
	if (arg_type == T_IND)
		return (2);
	if (arg_type == T_DIR)
		return (label);
	return (0);
}
