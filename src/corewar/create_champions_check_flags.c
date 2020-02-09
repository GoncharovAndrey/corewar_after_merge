/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_champions_check_flags.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by gmeizo            #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_champ					*create_suite_of_champions(int args,
						char **argv, t_map *map)
{
	int					fd;
	int					index;
	t_champ				*suite_of_champions;
	int					number_of_champion;

	index = 0;
	suite_of_champions = NULL;
	while (++index < args)
	{
		number_of_champion = check_flag_number(argv, args, &index, map);
		if (index >= args)
			break ;
		if (argv[index][0] == '-')
			check_flag_number(argv, args, &index, map);
		if (((fd = open(argv[index], O_RDONLY)) < 0))
			print_usage();
		create_add_champion_to_suite(fd, &suite_of_champions,
	number_of_champion);
	}
	!suite_of_champions ? print_usage() : 0;
	map->car_numb = count_champions(suite_of_champions);
	set_right_id_to_champ(suite_of_champions, 1);
	check_numbers_flags(suite_of_champions, map->car_numb);
	return (list_bubble_sort_champ(suite_of_champions, NULL, NULL, NULL));
}

void					create_add_champion_to_suite(int fd, t_champ **suite,
						int number_of_champion)
{
	t_champ				*new_champion;
	int					check_temp;
	int					pos;

	new_champion = parse_champ_information_from_file(init_champ(),
		fd, number_of_champion);
	if (!(new_champion->bot_code = (unsigned char *)malloc(sizeof(unsigned char)
		* (new_champion->bot_size + 1))))
		exit(1);
	pos = read(fd, new_champion->bot_code, new_champion->bot_size);
	if (pos < new_champion->bot_size || read(fd, &check_temp, 1) != 0)
		error_print_exit("File has a code size that differ "
	"from what its header says");
	new_champion->bot_code[pos] = '\0';
	ft_lst_champ_end(suite, new_champion);
}

int						count_champions(t_champ *suite_of_champions)
{
	t_champ				*temp_champion;
	int					amount_of_champions;

	amount_of_champions = 0;
	temp_champion = suite_of_champions;
	while (temp_champion)
	{
		amount_of_champions++;
		temp_champion = temp_champion->next_champ;
	}
	return (amount_of_champions);
}
