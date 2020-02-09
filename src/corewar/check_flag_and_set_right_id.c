/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag_and_set_right_id.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by gmeizo            #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void					check_flag_number_extra(char **argv, int args,
						int *index, t_map *map)
{
	if (!ft_strcmp("-dump", argv[*index]))
	{
		*index + 1 >= args ? print_usage() : 0;
		((map->dump = ft_atoi(argv[*index + 1])) <= 0) ? print_usage() : 0;
		*index += 2;
	}
	else if (!ft_strcmp("-d", argv[*index]))
	{
		*index + 1 >= args ? print_usage() : 0;
		if ((map->d = ft_atoi(argv[*index + 1])) <= 0)
			print_usage();
		*index += 2;
	}
	else if (!ft_strcmp("-v", argv[*index]))
	{
		map->visual = 1;
		*index += 1;
	}
	else if (!ft_strcmp("-a", argv[*index]))
	{
		map->aff_flag = 1;
		*index += 1;
	}
}

int						check_flag_number(char **argv, int args,
						int *index, t_map *map)
{
	int					number_of_champion;

	number_of_champion = 0;
	if (!ft_strcmp("-n", argv[*index]))
	{
		*index + 2 >= args ? print_usage() : 0;
		if ((number_of_champion = ft_atoi(argv[*index + 1])) <= 0)
			print_usage();
		*index += 2;
	}
	else
		check_flag_number_extra(argv, args, index, map);
	return (number_of_champion);
}

void					check_numbers_flags(t_champ *suite, int count_champ)
{
	t_champ				*temp;
	t_champ				*temp_2;
	int					numb;

	temp = suite;
	while (temp)
	{
		if (temp->const_int > count_champ || temp->const_int > MAX_PLAYERS)
			print_usage();
		temp = temp->next_champ;
	}
	temp = suite;
	while (temp)
	{
		numb = temp->const_int;
		temp_2 = temp->next_champ;
		while (temp_2)
		{
			(numb == temp_2->const_int && numb != 0) ? print_usage() : 0;
			temp_2 = temp_2->next_champ;
		}
		temp = temp->next_champ;
	}
}

void					set_right_id_to_champ(t_champ *suite_of_champions,
						int number)
{
	t_champ				*temp_ch;
	t_champ				*temp;

	temp = suite_of_champions;
	while (temp)
	{
		temp_ch = suite_of_champions;
		if (!temp->const_int)
		{
			while (temp_ch)
			{
				if (temp_ch->const_int == number)
				{
					number++;
					temp_ch = suite_of_champions;
					continue;
				}
				temp_ch = temp_ch->next_champ;
			}
			temp->id = number;
			temp->const_int = number;
		}
		temp = temp->next_champ;
		number = 0;
	}
}
