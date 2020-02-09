/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_car_champ.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by gmeizo            #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				zero_4_int(int *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

t_car				*init_car(int car_id, int i)
{
	t_car			*car;
	int				ind;

	ind = 0;
	if (!(car = (t_car *)malloc(sizeof(t_car))))
		return (NULL);
	car->arr_reg[0] = -car_id;
	car->id = car_id;
	ft_bzero(&car->suite_of_arg, 4);
	zero_4_int(&car->live, &car->carry,
			&car->number_of_command, &car->distance_from_command);
	car->i = i;
	car->next_car = NULL;
	car->last_live = 0;
	car->cycle_to_operation = 0;
	while (ind++ <= 16)
		car->arr_reg[ind] = 0;
	return (car);
}

t_map				*init_map(void)
{
	t_map			*map;

	if (!(map = (t_map *)ft_memalloc(sizeof(t_map) * 1)))
		return (NULL);
	if (!(map->map = (unsigned char *)
			ft_memalloc(sizeof(unsigned char) * MEM_SIZE)))
		return (NULL);
	if (!(map->color_map = (unsigned char *)
			ft_memalloc(sizeof(unsigned char) * MEM_SIZE)))
		return (NULL);
	if (!(map->bold = (unsigned char *)
			ft_memalloc(sizeof(unsigned char) * MEM_SIZE)))
		return (NULL);
	zero_4_int(&map->number_of_checks, &map->cycles, &map->dump, &map->d);
	zero_4_int(&map->last_car, &map->cycles_after_check,
			&map->all_lives, &map->pause);
	map->aff_flag = 0;
	map->add_operation = 0;
	map->cycles_to_die = 1536;
	map->delay = 14000;
	return (map);
}

t_champ				*init_champ(void)
{
	t_champ			*champ;

	if (!(champ = (t_champ *)malloc(sizeof(t_champ))))
		return (NULL);
	if (!(champ->bot_name = ft_strnew(PROG_NAME_LENGTH)))
		return (NULL);
	if (!(champ->bot_comment = ft_strnew(COMMENT_LENGTH)))
		return (NULL);
	champ->next_champ = NULL;
	return (champ);
}
