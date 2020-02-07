/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:05:53 by jgoyette          #+#    #+#             */
/*   Updated: 2020/01/31 21:06:18 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_set_champion_comment(t_data *data)
{
	if (data->champion_comment != NULL)
		ft_exit_with_syntax_error(data);
	data->curr_token = data->curr_token->next;
	if (data->curr_token->type != STRING)
		ft_exit_with_syntax_error(data);
	else if (ft_strlen(data->curr_token->content) > COMMENT_LENGTH)
		ft_exit_with_max_length_error(data, ERROR_COMMENT_LENGTH,
				COMMENT_LENGTH);
	else
		data->champion_comment = data->curr_token->content;
	data->curr_token = data->curr_token->next;
}

static void	ft_set_champion_name(t_data *data)
{
	if (data->champion_name != NULL)
		ft_exit_with_syntax_error(data);
	data->curr_token = data->curr_token->next;
	if (data->curr_token->type != STRING)
		ft_exit_with_syntax_error(data);
	else if (ft_strlen(data->curr_token->content) > PROG_NAME_LENGTH)
		ft_exit_with_max_length_error(data, ERROR_NAME_LENGTH,
				PROG_NAME_LENGTH);
	else
		data->champion_name = data->curr_token->content;
	data->curr_token = data->curr_token->next;
}

void		ft_set_commands(t_data *data)
{
	data->curr_token = data->tokens;
	while (data->curr_token && (data->curr_token->type == COMMAND_NAME
				|| data->curr_token->type == COMMAND_COMMENT))
	{
		if (ft_strequ(data->curr_token->content, COMMENT_CMD_STRING))
			ft_set_champion_comment(data);
		else if (ft_strequ(data->curr_token->content, NAME_CMD_STRING))
			ft_set_champion_name(data);
		else
			ft_exit_with_lexical_error(data, data->col + 1);
		if (data->curr_token->type != ENDLINE)
			ft_exit_with_syntax_error(data);
		data->curr_token = data->curr_token->next;
	}
	if (data->champion_name == NULL)
		ft_exit_with_error(data, ERROR_NO_NAME_COMMAND);
	else if (data->champion_comment == NULL)
		ft_exit_with_error(data, ERROR_NO_COMMENT_COMMAND);
}
