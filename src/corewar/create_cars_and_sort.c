/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cars_and_sort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by gmeizo            #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_car			*list_bubble_sort(t_car *head, t_car *temp,
				t_car *car, t_car *car_next)
{
	t_car		*all;
	t_car		*prev;

	all = head;
	while (all->next_car)
	{
		car = all;
		car_next = car->next_car;
		if (car->id < car_next->id && car == head)
		{
			head = replace_sort_start(&temp, &car_next, &car);
			all = car_next;
		}
		else if (car->id < car_next->id)
		{
			replace_sort_betw(&prev, &car_next, &temp, &car);
			all = head;
		}
		else
		{
			prev = all;
			all = all->next_car;
		}
	}
	return (head);
}

void			create_and_add_car_to_suite(int champion_number,
				t_car **suite_of_cars, int start_index, t_champ *champ)
{
	t_car		*new_car;

	new_car = init_car(champion_number, 0);
	ft_lst_car_start(suite_of_cars, new_car);
	(*suite_of_cars)->id = champ->id;
	(*suite_of_cars)->i = start_index;
}

t_car			*create_and_fit_all_cars(t_champ *suite_of_champions,
				int dist_car)
{
	t_car		*suite_of_cars;
	t_champ		*champ;
	int			champion_number;
	int			start_index;

	suite_of_cars = NULL;
	champ = suite_of_champions;
	champion_number = 1;
	start_index = 0;
	while (champ)
	{
		create_and_add_car_to_suite(champion_number,
									&suite_of_cars, start_index, champ);
		champ->const_int != suite_of_cars->id
		? champion_number = suite_of_cars->id : 0;
		(!champ->const_int) ? champion_number += 1 : 0;
		champ = champ->next_champ;
		start_index += dist_car;
	}
	return (list_bubble_sort(suite_of_cars, NULL, NULL, NULL));
}

t_car			*create_suite_of_cars(t_champ *suite_of_champions)
{
	t_car		*head;
	int			dist_car;

	dist_car = MEM_SIZE / count_champions(suite_of_champions);
	head = create_and_fit_all_cars(suite_of_champions, dist_car);
	return (head);
}
