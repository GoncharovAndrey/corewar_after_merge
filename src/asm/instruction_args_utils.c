/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_args_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:17:35 by jgoyette          #+#    #+#             */
/*   Updated: 2020/01/31 21:18:33 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_get_arg_code(int arg_type)
{
	if (arg_type == T_REG)
		return (REG_CODE);
	else if (arg_type == T_DIR)
		return (DIR_CODE);
	else if (arg_type == T_IND)
		return (IND_CODE);
	else
		return (0);
}

static int	ft_get_args_types_mask(t_data *data, t_token *token, t_op *op)
{
	int	i;
	int	arg_type;
	int	args_types_mask;

	i = 0;
	args_types_mask = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		args_types_mask <<= 2;
		if (i < op->nargs)
		{
			if ((arg_type = ft_get_arg_type(token->type)) &&
					(args_types_mask |= ft_get_arg_code(arg_type)))
				token = token->next;
			else
				ft_exit_with_syntax_error(data);
		}
		i += 1;
		while (i < op->nargs && token->type == SEPARATOR)
			token = token->next;
	}
	return (args_types_mask);
}

int			ft_get_arg_type(t_type type)
{
	if (type == REGISTER)
		return (T_REG);
	else if (type == DIRECT_LABEL || type == DIRECT_NUM)
		return (T_DIR);
	else if (type == INDIRECT_LABEL || type == INDIRECT_NUM)
		return (T_IND);
	else
		return (0);
}

void		ft_handle_args_types_code(t_data *data, t_op *op)
{
	t_token	*prev_token;
	t_token	*token;
	int		mask;

	prev_token = data->curr_token;
	data->curr_token = data->curr_token->next;
	mask = ft_get_args_types_mask(data, data->curr_token, op);
	if (!(token = ft_init_token(data, NULL, data->col, ARGS_TYPES)))
		ft_exit_with_error(data, ERROR_MALLOC);
	token->value = mask;
	token->size = 1;
	token->next = data->curr_token;
	prev_token->next = token;
	data->champion_code_size += 1;
}
