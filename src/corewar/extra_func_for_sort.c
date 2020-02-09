/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exta_func_for_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_champ					*replace_sort_start_ch(t_champ **temp,
						t_champ **car_next, t_champ **car)
{
	*temp = (*car_next)->next_champ;
	(*car_next)->next_champ = *car;
	(*car)->next_champ = *temp;
	return (*car_next);
}

void					replace_sort_betw_ch(t_champ **prev, t_champ **car_next,
						t_champ **temp, t_champ **car)
{
	(*prev)->next_champ = *car_next;
	*temp = (*car_next)->next_champ;
	(*car_next)->next_champ = *car;
	(*car)->next_champ = *temp;
}

t_car					*replace_sort_start(t_car **temp, t_car **car_next,
						t_car **car)
{
	*temp = (*car_next)->next_car;
	(*car_next)->next_car = *car;
	(*car)->next_car = *temp;
	return (*car_next);
}

void					replace_sort_betw(t_car **prev, t_car **car_next,
						t_car **temp, t_car **car)
{
	(*prev)->next_car = *car_next;
	*temp = (*car_next)->next_car;
	(*car_next)->next_car = *car;
	(*car)->next_car = *temp;
}

t_champ					*list_bubble_sort_champ(t_champ *head, t_champ *temp,
						t_champ *car, t_champ *car_next)
{
	t_champ				*all;
	t_champ				*prev;

	all = head;
	while (all->next_champ)
	{
		car = all;
		car_next = car->next_champ;
		if (car->id > car_next->id && car == head)
		{
			head = replace_sort_start_ch(&temp, &car_next, &car);
			all = car_next;
		}
		else if (car->id > car_next->id)
		{
			replace_sort_betw_ch(&prev, &car_next, &temp, &car);
			all = head;
		}
		else
		{
			prev = all;
			all = all->next_champ;
		}
	}
	return (head);
}
