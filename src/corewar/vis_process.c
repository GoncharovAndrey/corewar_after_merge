/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					players(WINDOW *help_win, int line, t_map *map)
{
	int				j;
	t_car			*tmp_car;
	t_champ			*temp_champ;

	temp_champ = map->all_champ;
	while (temp_champ)
	{
		wattron(help_win, COLOR_PAIR(temp_champ->id));
		mvwprintw(help_win, line++, 2, "Player %d : %s \n",
				temp_champ->id, temp_champ->bot_name);
		wattroff(help_win, COLOR_PAIR(temp_champ->id));
		tmp_car = map->start_car;
		j = 0;
		while (tmp_car)
		{
			temp_champ->id == tmp_car->id ? j++ : 0;
			tmp_car = tmp_car->next_car;
		}
		mvwprintw(help_win, line++, 2,
				"Lives in current period :\t\t%d    ", j);
		line++;
		temp_champ = temp_champ->next_champ;
	}
	return (line);
}

void				write_map_color(t_map *map, int pos, int len, t_car *temp)
{
	int				i;

	if (map->visual)
	{
		i = -1;
		while (++i < len)
		{
			map->color_map[get_index(pos + i)] = (unsigned char)(temp->id);
			map->bold[get_index(pos + i)] = 70;
		}
	}
}

void				end_game(t_map *map)
{
	t_champ			*temp;

	wattron(map->help_win, COLOR_PAIR(4));
	mvwprintw(map->help_win, 1, 2, "** END OF THE GAME **");
	wattroff(map->help_win, COLOR_PAIR(4));
	wattron(map->help_win, COLOR_PAIR(1));
	temp = map->all_champ;
	while (temp)
	{
		if (temp->id == map->last_car)
		{
			mvwprintw(map->help_win, 32, 2, "Winner ->[%d] %s ",
					map->last_car, temp->bot_name);
			break ;
		}
		temp = temp->next_champ;
	}
	wattroff(map->help_win, COLOR_PAIR(1));
	wrefresh(map->help_win);
}

void				stop_visual(t_map *map)
{
	if (map->visual)
	{
		end_game(map);
		while (1)
			if (getch() == 32)
			{
				delwin(map->game_win);
				delwin(map->help_win);
				endwin();
				exit(1);
			}
	}
}
