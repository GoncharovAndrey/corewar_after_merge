/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycles_to_die.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			delete_died_cursors(t_map *map)
{
	t_car		*previous;
	t_car		*current;
	t_car		*delete;

	previous = NULL;
	current = map->start_car;
	while (current)
	{
		delete = current;
		if (map->cycles_to_die <= 0 || map->cycles - current->last_live
		>= map->cycles_to_die)
		{
			current = current->next_car;
			if (map->start_car == delete)
				map->start_car = current;
			if (previous)
				previous->next_car = current;
			ft_memdel((void **)&delete);
		}
		else
		{
			previous = current;
			current = current->next_car;
		}
	}
}

void			check_cars_cycles(t_map *map)
{
	map->number_of_checks++;
	delete_died_cursors(map);
	if (map->number_of_checks == MAX_CHECKS || map->all_lives >= NBR_LIVE)
	{
		map->cycles_to_die -= CYCLE_DELTA;
		map->number_of_checks = 0;
	}
	map->all_lives = 0;
	map->cycles_after_check = 0;
}
