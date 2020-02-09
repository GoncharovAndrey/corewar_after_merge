/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_and_intro_end.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:19:27 by hwiegand          #+#    #+#             */
/*   Updated: 2019/07/18 18:23:01 by hwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void					print_usage(void)
{
	ft_dprintf(2, "./original [-dump N | -d N | -n N | -a]"
	"<champion1.cor> <...>\n");
	ft_dprintf(2, "-dump N      : Dumps memory after "
	"N cycles then exits (64-octet)\n");
	ft_dprintf(2, "-d N      : Dumps memory after "
	"N cycles then exits (32-octet)\n");
	ft_dprintf(2, "-n N      : Set N to the next player number\n");
	ft_dprintf(2, "-a        : Print output from ""aff"" (Default is off)\n");
	exit(-1);
}

t_champ					*introduce_the_champions(t_champ *champions)
{
	t_champ				*champ;
	int					number_champ;

	champ = champions;
	number_champ = 1;
	ft_printf("Introducing contestants...\n");
	while (champ)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				number_champ++, champ->bot_size,
				champ->bot_name, champ->bot_comment);
		champ = champ->next_champ;
	}
	return (champions);
}

void					print_winner(t_champ *suite_of_champions, t_map *map)
{
	t_champ				*temp;

	temp = suite_of_champions;
	while (temp)
	{
		if (temp->id == map->last_car)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n",
					map->last_car, temp->bot_name);
			break ;
		}
		temp = temp->next_champ;
	}
}

void					print_map_output_dump(t_map *map)
{
	int	i;
	int	j;
	int len;

	i = 0;
	len = (map->d) ? 32 : 64;
	while (i < MEM_SIZE)
	{
		j = 0;
		ft_printf("0x%.4x : ", i);
		while (j < len)
		{
			ft_printf("%.2x ", map->map[i + j]);
			j++;
		}
		ft_printf("\n");
		i += len;
	}
	exit(1);
}
