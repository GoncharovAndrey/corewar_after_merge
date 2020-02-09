/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by gmeizo            #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void					ft_lst_champ_end(t_champ **lst_champ,
						t_champ *new_champ)
{
	t_champ				*tmp;

	tmp = *lst_champ;
	if (tmp == NULL)
		*lst_champ = new_champ;
	else
	{
		while (tmp->next_champ)
			tmp = tmp->next_champ;
		tmp->next_champ = new_champ;
	}
}

void					ft_lst_car_start(t_car **lst_car, t_car *new_car)
{
	t_car				*tmp;

	tmp = *lst_car;
	if (tmp == NULL)
		*lst_car = new_car;
	else
	{
		new_car->next_car = tmp;
		*lst_car = new_car;
	}
}

t_car					*remove_car(t_map *map, t_car *temp)
{
	map->start_car = temp->next_car;
	free(temp);
	temp = map->start_car;
	return (temp);
}

t_champ					*remove_champ(t_map *map, t_champ *temp)
{
	map->all_champ = temp->next_champ;
	free(temp);
	temp = map->all_champ;
	return (temp);
}

void					free_map(t_map *map)
{
	t_car				*temp_car;
	t_champ				*temp_champ;

	free(map->map);
	free(map->color_map);
	free(map->bold);
	temp_car = map->start_car;
	while (temp_car)
		temp_car = remove_car(map, temp_car);
	temp_champ = map->all_champ;
	while (temp_champ)
	{
		free(temp_champ->bot_name);
		free(temp_champ->bot_comment);
		free(temp_champ->bot_code);
		temp_champ = remove_champ(map, temp_champ);
	}
	free(map);
}
