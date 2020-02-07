/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_labels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:20:02 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/04 17:49:23 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_new_label_needed(t_token **labels, const char *content)
{
	t_token *tmp;

	if (labels)
	{
		tmp = *labels;
		while (tmp)
		{
			if (tmp->content == content)
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

static int	ft_find_label_distance(t_data *data, int token_pos, t_token *token)
{
	t_token		*label;
	const char	*token_content;
	int			label_len;
	int			token_len;

	if (token->type == DIRECT_LABEL)
		token_content = token->content + 2;
	else
		token_content = token->content + 1;
	token_len = ft_strlen(token_content);
	label = data->labels;
	while (label)
	{
		label_len = ft_strlen(label->content) - 1;
		if (token_len == label_len && ft_strnequ(label->content,
										token_content, label_len))
			return (label->pos - token_pos);
		label = label->next;
	}
	ft_exit_with_no_such_label_error(data, token);
	return (0);
}

void		ft_set_label_values(t_data *data)
{
	t_token	*curr_token;
	t_token	*start_token;

	curr_token = data->start_code_token;
	while (curr_token)
	{
		if (curr_token->type == INSTRUCTION)
			start_token = curr_token;
		else if (curr_token->type == DIRECT_LABEL
				|| curr_token->type == INDIRECT_LABEL)
			curr_token->value = ft_find_label_distance(data,
										start_token->pos, curr_token);
		curr_token = curr_token->next;
	}
}

void		ft_handle_ignorable_label(t_data *data)
{
	if (ft_new_label_needed(&data->labels, data->curr_token->content))
		ft_add_token(&data->labels, ft_init_label(data,
					data->curr_token->content, data->champion_code_size));
	data->curr_token->pos = data->champion_code_size;
}

void		ft_handle_replaceable_label(t_data *data, t_op *op)
{
	int		arg_size;

	if (data->curr_token->type == DIRECT_LABEL)
		arg_size = op->t_dir_size;
	else
		arg_size = 2;
	data->curr_token->size = arg_size;
	data->curr_token->pos = data->champion_code_size;
	data->champion_code_size += arg_size;
}
