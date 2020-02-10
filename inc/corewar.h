/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _COREWAR_H
# define _COREWAR_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <curses.h>
# include <ncurses.h>
# include "op.h"

# define GET_BYTE -1
# define CUT_MDX 1
# define NO_CUT 0

typedef struct				s_list_champ
{
	char					*bot_name;
	char					*bot_comment;
	unsigned char			*bot_code;
	unsigned int			arr_reg[REG_NUMBER];
	int						bot_size;
	int						const_int;
	int						id;
	struct s_list_champ		*next_champ;
}							t_champ;

typedef struct				s_list_car
{
	int						arr_reg[REG_NUMBER];
	int						suite_of_arg[4];
	int						carry;
	int						cycle_to_operation;
	int						i;
	int						distance_from_command;
	int						number_of_command;
	int						id;
	int						live;
	int						last_live;
	struct s_list_car		*next_car;
}							t_car;

typedef struct				s_list_main
{
	unsigned char			*map;
	t_car					*start_car;
	int						car_numb;
	int						all_lives;
	int						last_car;
	int						cycles;
	int						dump;
	int						d;
	int						cycles_to_die;
	int						number_of_checks;
	int						cycles_after_check;
	int                     add_operation;
	unsigned char			*bold;
	unsigned char			*color_map;
	t_champ					*all_champ;
	int						visual;
	int						aff_flag;
	int						delay;
	WINDOW					*game_win;
	WINDOW					*help_win;
	int						pause;
}							t_map;

typedef struct				s_op
{
	char					*name;
	int						code;
	int						argument_count;
	int						suite_of_arg[3];
	int						label;
	unsigned int			cycles;
	int						codage_octal;
	int						(*func)(t_car *, t_map *);
}							t_op;

/*
** main.c
*/

void						execute_operation_by_car(t_car *car, t_map *map);
void						execute_game_on_map(t_map *map);

/*
**	adder.c
*/

void						error_print_exit(char *temp);
void						read_endl(int size, int fd, char **str);
int							time_to_check_cycles(t_map *map);
int							valid_parameters(int args);
int							get_index(int coord);

/*
**	check_arguments_cycles.c
*/

int							check_cycle_and_substruct(t_car *car, t_map *map);
int							check_valid_argumemts_and_reg(t_car *car,
							t_map *map);
int							distance_to_next_command(t_car *car);
int							distanse_length(int arg_type, int label);

/*
**	check_cycles_to_die.c
*/

void						delete_died_cursors(t_map *map);
void						check_cars_cycles(t_map *map);

/*
**	check_flag_and_set_right_id.c
*/

void						check_flag_number_extra(char **argv, int args,
							int *index, t_map *map);
int							check_flag_number(char **argv, int args,
							int *index, t_map *map);
void						check_numbers_flags(t_champ *suite,
							int count_champ);
void						set_right_id_to_champ(t_champ *suite_of_champions,
							int number);

/*
**	create_cars_and_sort.c
*/

t_car						*list_bubble_sort(t_car *head, t_car *temp,
							t_car *car, t_car *car_next);
void						create_and_add_car_to_suite(int champion_number,
		t_car **suite_of_cars, int start_index, t_champ *champ);
t_car						*create_and_fit_all_cars(t_champ
							*suite_of_champions, int dist_car);
t_car						*create_suite_of_cars(t_champ *suite_of_champions);

/*
**	create_champions_check_flags.c
*/

t_champ						*create_suite_of_champions(int args,
							char **argv, t_map *map);
void						create_add_champion_to_suite(int fd,
							t_champ **suite, int number_of_champion);
int							count_champions(t_champ *suite_of_champions);

/*
**	extra_func_for_sort.c
*/

t_car						*replace_sort_start(t_car **temp, t_car **car_next,
							t_car **car);
void						replace_sort_betw(t_car **prev, t_car **car_next,
							t_car **temp, t_car **car);
t_champ						*list_bubble_sort_champ(t_champ *head,
		t_champ *temp, t_champ *car, t_champ *car_next);

/*
**	functions_to_put_take_from_memory.c
*/

int							get_register_from_byte(t_map *map, t_car *car);
int							get_value_from_argument(t_map *map, t_car *car,
							int index, int action);
void						put_from_int_to_map(unsigned char *map, int index,
							int value, int label);
int							from_memory_to_int(unsigned char *map, int addr,
							int label);

/*
**	init_map_car_champ.c
*/

t_car						*init_car(int car_id, int i);
t_map						*init_map(void);
t_champ						*init_champ(void);

/*
**	list_operations.c
*/

void						ft_lst_champ_end(t_champ **lst_champ,
							t_champ *new_champ);
void						ft_lst_car_start(t_car **lst_car, t_car *new_car);
void						free_map(t_map *map);

/*
**	parse_champions_info.c
*/

t_champ						*parse_champ_information_from_file(t_champ
							*champion, int fd, int check_number_flag);
void						get_arguments_from_byte(t_map *map, t_car *car);

/*
** print_map_and_intro_end.c
*/

void						print_usage(void);
t_champ						*introduce_the_champions(t_champ *champions);
void						print_winner(t_champ *suite_of_champions,
							t_map *map);
void						print_map_output_dump(t_map *map);

/*
**	put_code_and_indexes_to_map.c
*/

t_car						*put_start_index_to_cars(t_car *suite_cars,
							t_map *map);
void						memset_colormap(t_map *map);
void						put_code_champions_to_map(t_map *map,
							t_champ *suite_of_champions);

/*
**	vis_extra_func.c
*/

t_car						*remove_head(t_map *map, t_car *temp);
void						free_cor(t_map *map);
WINDOW						*create_newwin(int height, int width, int starty,
							int startx);
void						create_field(t_map *map);

/*
**vis_map.c
*/

void						panel_help(t_map *map, WINDOW *game_win,
							int i, int line);
void						paint_carg(t_map *map);
int							graph_cycle(t_map *map);
void						visual(t_map *map);

/*
** 	vis_process.c
*/

int							players(WINDOW *help_win, int line, t_map *map);
void						write_map_color(t_map *map, int pos, int len,
							t_car *temp);
void						end_game(t_map *map);
void						stop_visual(t_map *map);

/*
** vis_window.c
*/

void						help_panel(WINDOW *help_win, t_map *map);
void						game_panel(WINDOW *game_win, t_map *map);
void						draw(t_map *map);
void						open_window(t_map *map);

/*
** _operations/
*/

int							and(t_car *car, t_map *map);
int							sti(t_car *car, t_map *map);
int							zjmp(t_car *car, t_map *map);
int							xor(t_car *car, t_map *map);
int							sub(t_car *car, t_map *map);
int							sti(t_car *car, t_map *map);
int							st(t_car *car, t_map *map);
int							or(t_car *car, t_map *map);
int							lldi(t_car *car, t_map *map);
int							lld(t_car *car, t_map *map);
int							ldi(t_car *car, t_map *map);
int							ld (t_car *car, t_map *map);
int							aff(t_car *car, t_map *map);
int							add(t_car *car, t_map *map);
int							live(t_car *car, t_map *map);
int							lfork(t_car *car, t_map *map);
int							ffork(t_car *car, t_map *map);
int 						fastfork(t_car *car, t_map *map);
int 						trap(t_car *car, t_map *map);

t_car						*copy_car(t_car *car, int value);

static t_op		g_op[19] =
{
	{	.name = "zero", .code = 0x01, .argument_count = 0,
		.suite_of_arg = {0, 0, 0}, .label = 0,
		.cycles = 0, .codage_octal = 0, .func = NULL },
	{	.name = "live", .code = 0x01, .argument_count = 1,
		.suite_of_arg = {T_DIR, 0, 0}, .label = 4,
		.cycles = 10, .codage_octal = 0, .func = &live },
	{	.name = "ld", .code = 0x02, .argument_count= 2,
		.suite_of_arg = {T_DIR | T_IND, T_REG, 0}, .label = 4,
		.cycles = 5, .codage_octal = 1, .func = &ld },
	{	.name = "st", .code = 0x03, .argument_count= 2,
		.suite_of_arg = {T_REG, T_REG | T_IND, 0}, .label = 4,
		.cycles = 5, .codage_octal = 1, .func = &st },
	{	.name = "add", .code = 0x04, .argument_count= 3,
		.suite_of_arg = {T_REG, T_REG, T_REG}, .label = 4,
		.cycles = 10, .codage_octal = 1, .func = &add },
	{	.name = "sub", .code = 0x05, .argument_count= 3,
		.suite_of_arg = {T_REG, T_REG, T_REG}, .label = 4,
		.cycles = 10, .codage_octal = 1, .func = &sub},
	{	.name = "and", .code = 0x06, .argument_count= 3,
		.suite_of_arg = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.label = 4, .cycles = 6, .codage_octal = 1, .func = &and},
	{	.name = "or", .code = 0x07, .argument_count= 3,
		.suite_of_arg = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.label = 4, .cycles = 6, .codage_octal = 1, .func = &or},
	{	.name = "xor", .code = 0x08, .argument_count = 3,
		.suite_of_arg = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.label = 4, .cycles = 6, .codage_octal = 1, .func = &xor},
	{	.name = "zjmp", .code = 0x09, .argument_count= 1,
		.suite_of_arg = {T_DIR, 0, 0}, .label = 2,
		.cycles = 20, .codage_octal = 0, .func = &zjmp},
	{	.name = "ldi", .code = 0x0A, .argument_count = 3,
		.suite_of_arg = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.label = 2, .cycles = 25, .codage_octal = 1, .func = &ldi},
	{	.name = "sti", .code = 0x0B, .argument_count= 3,
		.suite_of_arg = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.label = 2, .cycles = 25, .codage_octal = 1, .func = &sti},
	{	.name = "fork", .code = 0x0C, .argument_count= 1,
		.suite_of_arg = {T_DIR, 0, 0}, .label = 2,
		.cycles = 800, .codage_octal = 0, .func = &ffork},
	{	.name = "lld", .code = 0x0D, .argument_count= 2,
		.suite_of_arg = {T_DIR | T_IND, T_REG, 0}, .label = 4,
		.cycles = 10, .codage_octal = 1, .func = &lld},
	{	.name = "lldi", .code = 0x0E, .argument_count= 3,
		.suite_of_arg = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.label = 2, .cycles = 50, .codage_octal = 1, .func = &lldi},
	{	.name = "lfork", .code = 0x0F, .argument_count= 1,
		.suite_of_arg = {T_DIR, 0, 0}, .label = 2,
		.cycles = 1000, .codage_octal = 0, .func = &lfork },
	{	.name = "aff", .code = 0x10, .argument_count = 1,
		.suite_of_arg = {T_REG, 0, 0}, .label = 4,
		.cycles = 2, .codage_octal = 1, .func = &aff },
    {	.name = "fastfork",	.code = 0x11, .argument_count = 1,
            .suite_of_arg = {T_DIR, 0, 0}, .label = 2,
            .cycles = 600, .codage_octal = 0, .func = &fastfork },
    {	.name = "trap", .code = 0x12, .argument_count = 1,
            .suite_of_arg = {T_DIR, 0, 0}, .label = 4,
            .cycles = 2, .codage_octal = 0, .func = &trap}
};

#endif
