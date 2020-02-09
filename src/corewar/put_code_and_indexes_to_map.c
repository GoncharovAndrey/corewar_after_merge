/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_code_and_indexes_to_map.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by gmeizo            #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_car				*put_start_index_to_cars(t_car *suite_cars, t_map *map)
{
	t_car			*temp_car;
	int				start_index;
	int				distination_between_cars;

	start_index = 0;
	temp_car = suite_cars;
	distination_between_cars = MEM_SIZE / map->car_numb;
	while (temp_car)
	{
		temp_car->arr_reg[0] = -temp_car->id;
		start_index += distination_between_cars;
		if (temp_car->id == map->car_numb)
			map->last_car = temp_car->id;
		temp_car = temp_car->next_car;
	}
	return (suite_cars);
}

void				memset_colormap(t_map *map)
{
	unsigned int	k;
	int				i;
	t_champ			*temp;

	i = 0;
	temp = map->all_champ;
	while (temp)
	{
		k = 0;
		while ((int)k < temp->bot_size)
		{
			map->color_map[k + i * (MEM_SIZE / map->car_numb)] = i + 1;
			k++;
		}
		temp = temp->next_champ;
		i++;
	}
}

void				put_code_champions_to_map(t_map *map,
					t_champ *suite_of_champions)
{
	t_champ			*temp_champion;
	int				start_car_position;
	int				distination_between_cars;
	int				i;
	int				j;

	start_car_position = 0;
	temp_champion = suite_of_champions;
	distination_between_cars = MEM_SIZE / map->car_numb;
	memset_colormap(map);
	while (temp_champion)
	{
		i = start_car_position;
		j = -1;
		while (++j < temp_champion->bot_size)
		{
			map->map[i] = temp_champion->bot_code[j];
			i++;
		}
		start_car_position += distination_between_cars;
		temp_champion = temp_champion->next_champ;
	}
}
