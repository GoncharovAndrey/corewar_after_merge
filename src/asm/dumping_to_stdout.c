/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumping_to_stdout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:49:41 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/04 18:52:05 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_print_bytes(unsigned int size, int value)
{
	if (size == 4)
	{
		ft_printf("%-4d", ((value >> 24) & 0xFF));
		ft_printf("%-4d", ((value >> 16) & 0xFF));
		ft_printf("%-4d", ((value >> 8) & 0xFF));
		ft_printf("%-6d", (value & 0xFF));
	}
	else
	{
		ft_printf("%-4d", ((value >> 8) & 0xFF));
		ft_printf("%-14d", (value & 0xFF));
	}
}

static void	ft_print_instruction_and_args(t_token *token)
{
	ft_printf("%-10s", token->content);
	token = token->next;
	while (token && token->type != INSTRUCTION)
	{
		if (ft_get_arg_type(token->type))
			ft_printf("%-18s", token->content);
		token = token->next;
	}
	ft_printf("\n");
}

static void	ft_print_args(t_token *token, int print_bytes)
{
	while (token && token->type != INSTRUCTION)
	{
		if (print_bytes)
		{
			if (token->type == REGISTER)
				ft_printf("%-18d", token->value);
			else if (token->type == INDIRECT_LABEL
					|| token->type == INDIRECT_NUM
					|| token->type == DIRECT_LABEL
					|| token->type == DIRECT_NUM)
				ft_print_bytes(token->size, token->value);
		}
		else
		{
			if (ft_get_arg_type(token->type))
				ft_printf("%-18d", token->value);
		}
		token = token->next;
	}
}

static void	ft_print_instruction_and_args_values(t_token *token,
													int print_bytes)
{
	if (token->value >= 10)
		ft_printf("%22d  ", token->value);
	else
		ft_printf("%21d   ", token->value);
	token = token->next;
	if (token->type == ARGS_TYPES)
	{
		ft_printf("%-6d", token->value);
		token = token->next;
	}
	else
		ft_printf("      ");
	ft_print_args(token, print_bytes);
	ft_printf("\n");
}

void		ft_dump_to_stdout(t_data *data)
{
	t_token			*token;
	unsigned int	size;

	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %u bytes\n", data->champion_code_size);
	ft_printf("Name : \"%s\"\n", data->champion_name);
	ft_printf("Comment : \"%s\"\n\n", data->champion_comment);
	token = data->start_code_token;
	while (token)
	{
		if (token->type == LABEL)
			ft_printf("%-11u:    %s\n", token->pos, token->content);
		else if (token->type == INSTRUCTION)
		{
			size = ft_get_insruction_line_size(token);
			ft_printf("%-5u(%-3u) :        ", token->pos, size);
			ft_print_instruction_and_args(token);
			ft_print_instruction_and_args_values(token, PRINT_BYTES);
			ft_print_instruction_and_args_values(token, NO_BYTES);
			ft_printf("\n");
		}
		token = token->next;
	}
}
