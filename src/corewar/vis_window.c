/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	help_panel(WINDOW *help_win, t_map *map)
{
	int line;

	line = 7;
	if (map->pause == 0)
	{
		wattron(help_win, COLOR_PAIR(2));
		mvwprintw(help_win, 1, 2, "** PAUSED **");
		wattroff(help_win, COLOR_PAIR(2));
	}
	else
	{
		wattron(help_win, COLOR_PAIR(1));
		mvwprintw(help_win, 1, 2, "** RUNNING **");
		wattroff(help_win, COLOR_PAIR(1));
	}
	mvwprintw(help_win, 3, 2, "Cycle : %d ", map->cycles);
	mvwprintw(help_win, 5, 2, "Processes : %d ", map->car_numb);
	line = players(help_win, line, map);
	mvwprintw(help_win, line, 2, "CYCLE_TO_DIE : %d ", map->cycles_to_die);
	mvwprintw(help_win, line + 2, 2, "CYCLE_DELTA : %d ", CYCLE_DELTA);
	mvwprintw(help_win, 23, 2, "DELTA_TIME_PRINT : %d ", map->delay);
}

void	game_panel(WINDOW *game_win, t_map *map)
{
	int		i;
	int		line;

	line = 1;
	i = -1;
	while (++i < 64)
	{
		panel_help(map, game_win, i, line);
		line++;
	}
	paint_carg(map);
}

void	draw(t_map *map)
{
	curs_set(0);
	usleep(map->delay);
	help_panel(map->help_win, map);
	game_panel(map->game_win, map);
	box(map->help_win, 0, 0);
	box(map->game_win, 0, 0);
	wrefresh(map->game_win);
	wrefresh(map->help_win);
}

void	open_window(t_map *map)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	create_field(map);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_BLACK, COLOR_RED);
	init_pair(13, COLOR_BLACK, COLOR_BLUE);
	init_pair(14, COLOR_BLACK, COLOR_CYAN);
	refresh();
}
