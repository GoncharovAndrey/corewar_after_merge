/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 20:39:53 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/07 18:54:27 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_print_usage(char *bin_name)
{
	ft_printf("Usage: %s [-a] <sourcefile.s>\n", bin_name);
	ft_printf("    -a : Instead of creating a .cor file, outputs a stripped "
	"and annotated version of the code to the standard output\n");
}

static void	ft_assembler(char *filename, int flag)
{
	t_data	*data;

	data = ft_init_data(filename);
	ft_parse_file(data);
	ft_set_commands(data);
	ft_set_code(data);
	if (flag == FLAG_A)
		ft_dump_to_stdout(data);
	else
		ft_write_to_file(data);
	ft_clean_data(data);
}

int			main(int argc, char **argv)
{
	if (argc == 2 && ft_has_extension(argv[1], ".s"))
		ft_assembler(argv[1], NO_FLAG);
	else if (argc == 3 && ft_strequ(argv[1], "-a")
				&& ft_has_extension(argv[2], ".s"))
		ft_assembler(argv[2], FLAG_A);
	else
		ft_print_usage(argv[0]);
	return (0);
}
