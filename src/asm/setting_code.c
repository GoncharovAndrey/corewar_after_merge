/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:03:19 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/07 18:55:20 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_handle_instruction(t_data *data)
{
	t_op	*op;

	if ((op = ft_get_op(data->curr_token->content)))
	{
		data->curr_token->value = op->code;
		data->curr_token->size = 1;
		data->curr_token->pos = data->champion_code_size;
		data->champion_code_size += 1;
		if (op->args_types_mask)
			ft_handle_args_types_code(data, op);
		else
			data->curr_token = data->curr_token->next;
		ft_handle_args(data, op);
	}
	else
		ft_exit_with_invalid_instruction_error(data);
}

void		ft_set_code(t_data *data)
{
	data->start_code_token = data->curr_token;
	while (data->curr_token)
	{
		if (data->curr_token->type == LABEL)
		{
			ft_handle_ignorable_label(data);
			data->curr_token = data->curr_token->next;
		}
		if (data->curr_token->type == INSTRUCTION)
			ft_handle_instruction(data);
		if (data->curr_token->type == ENDLINE)
			data->curr_token = data->curr_token->next;
		else
			ft_exit_with_syntax_error(data);
	}
	ft_set_label_values(data);
}
