/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int						main(int args, char **argv)
{
	t_champ				*suite_of_champions;
	t_car				*suite_of_cars;
	t_map				*map;

	if (valid_parameters(args))
	{
		map = init_map();
		suite_of_champions = create_suite_of_champions(args, argv, map);
		suite_of_cars = create_suite_of_cars(suite_of_champions);
		suite_of_champions = list_bubble_sort_champ(suite_of_champions,
													NULL, NULL, NULL);
		suite_of_cars = put_start_index_to_cars(suite_of_cars, map);
		map->all_champ = introduce_the_champions(suite_of_champions);
		put_code_champions_to_map(map, map->all_champ);
		map->start_car = suite_of_cars;
		map->visual == 1 ? open_window(map) : 0;
		execute_game_on_map(map);
		print_winner(map->all_champ, map);
		free_map(map);
	}
	else
		print_usage();
	return (0);
}

void					execute_operation_by_car(t_car *car, t_map *map)
{
	if (car->number_of_command >= 1 && car->number_of_command <=
	(16 + map->add_operation))
	{
		get_arguments_from_byte(map, car);
		if (check_valid_argumemts_and_reg(car, map))
			g_op[car->number_of_command].func(car, map);
		else
			car->distance_from_command += distance_to_next_command(car);
	}
	else
		car->distance_from_command = 1;
	car->i += car->distance_from_command;
	car->i = get_index(car->i);
	car->distance_from_command = 0;
	ft_bzero(car->suite_of_arg, 4);
}

void					execute_game_on_map(t_map *map)
{
	t_car				*car;

	while (map->start_car)
	{
		map->cycles_after_check++;
		map->cycles++;
		car = map->start_car;
		while (car)
		{
			if (check_cycle_and_substruct(car, map))
				execute_operation_by_car(car, map);
			car = car->next_car;
		}
		if (time_to_check_cycles(map))
			check_cars_cycles(map);
		if (map->cycles == map->d || map->cycles == map->dump)
			print_map_output_dump(map);
		map->visual ? visual(map) : 0;
	}
	map->visual ? stop_visual(map) : 0;
}
