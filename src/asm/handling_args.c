/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:55:52 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/07 18:55:55 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_handle_register(t_data *data)
{
	data->curr_token->value = ft_atoi(data->curr_token->content + 1);
	data->curr_token->size = 1;
	data->champion_code_size += 1;
}

static void	ft_handle_num(t_data *data, t_op *op)
{
	int arg_size;

	if (data->curr_token->type == DIRECT_NUM)
	{
		data->content = data->curr_token->content + 1;
		arg_size = op->t_dir_size;
		data->curr_token->value = (int)ft_atoui_max(data->content);
	}
	else
	{
		arg_size = 2;
		data->curr_token->value = (int)ft_atoui_max(data->curr_token->content);
	}
	data->curr_token->size = arg_size;
	data->champion_code_size += arg_size;
	data->content = NULL;
}

static void	ft_handle_arg(t_data *data, t_op *op, int i, int arg_type)
{
	if (i >= op->nargs || !(arg_type & op->args_types[i]))
		ft_exit_with_arg_type_error(data, i, arg_type, op->name);
	if (data->curr_token->type == REGISTER)
		ft_handle_register(data);
	else if (data->curr_token->type == DIRECT_LABEL ||
			data->curr_token->type == INDIRECT_LABEL)
		ft_handle_replaceable_label(data, op);
	else
		ft_handle_num(data, op);
}

void		ft_handle_args(t_data *data, t_op *op)
{
	int	i;
	int	arg_type;

	i = 0;
	arg_type = ft_get_arg_type(data->curr_token->type);
	if (!arg_type)
		ft_exit_with_syntax_error(data);
	while (arg_type)
	{
		ft_handle_arg(data, op, i, arg_type);
		data->curr_token = data->curr_token->next;
		i += 1;
		if (data->curr_token->type != SEPARATOR && i < op->nargs)
			ft_exit_with_syntax_error(data);
		if (data->curr_token->type == SEPARATOR)
		{
			data->curr_token = data->curr_token->next;
			if (!ft_get_arg_type(data->curr_token->type))
				ft_exit_with_syntax_error(data);
		}
		arg_type = ft_get_arg_type(data->curr_token->type);
	}
}
