/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting_with_non_positional_error.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 20:43:20 by jgoyette          #+#    #+#             */
/*   Updated: 2020/01/31 20:44:25 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_exit_with_io_error(t_data *data, const char *error_msg,
												const char *filename)
{
	ft_dprintf(STDERR_FILENO, "%s %s\n", error_msg, filename);
	ft_clean_data(data);
	exit(EXIT_FAILURE);
}

void	ft_exit_with_max_length_error(t_data *data, const char *error_msg,
																int length)
{
	ft_dprintf(STDERR_FILENO, "%s (Max length %d)\n", error_msg, length);
	ft_clean_data(data);
	exit(EXIT_FAILURE);
}

void	ft_exit_with_error(t_data *data, char *error_msg)
{
	ft_dprintf(STDERR_FILENO, "%s\n", error_msg);
	ft_clean_data(data);
	exit(EXIT_FAILURE);
}

void	ft_exit_with_arg_type_error(t_data *data, int arg_num,
							int arg_type, const char *instruction)
{
	const char	*type;

	if (arg_type == T_REG)
		type = "register";
	else if (arg_type == T_DIR)
		type = "direct";
	else if (arg_type == T_IND)
		type = "indirect";
	else
		type = "unknown";
	ft_dprintf(STDERR_FILENO, "Invalid parameter %d type " \
			"%s for instruction %s\n", arg_num, type, instruction);
	ft_clean_data(data);
	exit(EXIT_FAILURE);
}
