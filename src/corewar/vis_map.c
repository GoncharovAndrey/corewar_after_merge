/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				panel_help(t_map *map, WINDOW *game_win,
					int i, int line)
{
	int	col;
	int	j;

	col = 2;
	j = -1;
	while (++j < 64)
	{
		if (map->bold[i * 64 + j] && (map->bold[i * 64 + j] -= 1))
			wattron(game_win, A_BOLD);
		wattron(game_win, COLOR_PAIR(map->color_map[i * 64 + j]));
		if (map->map[i * 64 + j] < 0)
			mvwprintw(game_win, line, col, "%.2x ",
					256 + 1 * map->map[i * 64 + j]);
		else
			mvwprintw(game_win, line, col, "%.2x ", map->map[i * 64 + j]);
		wattroff(game_win, COLOR_PAIR(map->color_map[i * 64 + j]));
		if (map->bold[i * 64 + j])
			wattroff(game_win, A_BOLD);
		col += 3;
	}
}

void				paint_carg(t_map *map)
{
	t_car			*temp;
	int				color;

	temp = map->start_car;
	while (temp)
	{
		temp->i_vis = get_index(temp->i_vis);
		color = map->color_map[temp->i_vis] + 10;
		wattron(map->game_win, COLOR_PAIR(color));
		mvwprintw(map->game_win, temp->i_vis / 64 + 1,
				2 + (temp->i_vis % 64) * 3, "%.2x", map->map[temp->i_vis]);
		wattroff(map->game_win, COLOR_PAIR(color));
		temp = temp->next_car;
	}
	wrefresh(map->game_win);
}

int					graph_cycle(t_map *map)
{
	MEVENT			event;
	int				ch;

	ch = getch();
	if (ch == 27)
		return (1);
	if (ch == ' ')
		map->pause = (++map->pause) % 2;
	else if (ch == '+' && map->delay <= 50000)
		map->delay += 1000;
	else if (ch == '-' && map->delay > 1000)
		map->delay -= 1000;
	else if (ch == KEY_MOUSE)
	{
		if (getmouse(&event) == OK)
			;
	}
	return (0);
}

void				visual(t_map *map)
{
	draw(map);
	graph_cycle(map);
	while (map->pause == 0)
	{
		wattron(map->help_win, COLOR_PAIR(2));
		mvwprintw(map->help_win, 1, 2, "** PAUSED  **");
		wattroff(map->help_win, COLOR_PAIR(2));
		mvwprintw(map->help_win, 23, 2, "DELTA_TIME_PRINT : %d ",
				map->delay);
		wrefresh(map->help_win);
		if (graph_cycle(map) == 1)
		{
			delwin(map->game_win);
			delwin(map->help_win);
			free_cor(map);
			endwin();
			exit(1);
		}
	}
}
