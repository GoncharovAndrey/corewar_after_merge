/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_extra_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_car			*remove_head(t_map *map, t_car *temp)
{
	map->start_car = temp->next_car;
	free(temp);
	temp = map->start_car;
	return (temp);
}

void			free_cor(t_map *map)
{
	t_car		*temp;

	free(map->map);
	free(map->color_map);
	free(map->bold);
	temp = map->start_car;
	while (temp)
		temp = remove_head(map, temp);
	free(map);
}

WINDOW			*create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);
	wrefresh(local_win);
	return (local_win);
}

void			create_field(t_map *map)
{
	map->game_win = create_newwin(66, 195, 1, 3);
	map->help_win = create_newwin(66, 70, 1, 200);
	nodelay(map->game_win, 1);
	nodelay(map->help_win, 1);
	draw(map);
}
