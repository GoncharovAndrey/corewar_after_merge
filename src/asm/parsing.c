/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:15:15 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/04 17:48:48 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_new_line_needed(t_token **tokens)
{
	t_token *tmp;

	if (tokens)
	{
		tmp = *tokens;
		if (tmp)
		{
			while (tmp->next)
				tmp = tmp->next;
			if (tmp->type == ENDLINE)
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

static void	ft_handle_separator(t_data *data)
{
	if (!(data->content = ft_strnew(1)))
		ft_exit_with_error(data, ERROR_MALLOC);
	*data->content = SEPARATOR_CHAR;
	ft_add_token(&data->tokens, ft_init_token(data, data->content,
				data->col, SEPARATOR));
	data->content = NULL;
	data->col += 1;
}

static void	ft_parse_token(t_data *data)
{
	if (data->line[data->col] == CMD_START_CHAR)
		ft_parse_command(data, data->line);
	else if (data->line[data->col] == '"')
		ft_parse_string(data);
	else if (data->line[data->col] == SEPARATOR_CHAR)
		ft_handle_separator(data);
	else if (data->line[data->col] == DIRECT_CHAR)
		ft_parse_direct(data, data->line);
	else if ((data->line[data->col] == '+' || data->line[data->col] == '-')
			|| ft_isdigit(data->line[data->col]))
		ft_parse_num(data, data->line);
	else
		ft_parse_alpha(data, data->line);
}

static void	ft_parse_line(t_data *data)
{
	while (data->line[data->col] && data->line[data->col] != '\n')
	{
		while (ft_is_whitespace(data->line[data->col]))
			data->col += 1;
		if (data->line[data->col] == COMMENT_CHAR
				|| data->line[data->col] == ALT_COMMENT_CHAR)
		{
			while (data->line[data->col] && data->line[data->col] != '\n')
				data->col += 1;
			break ;
		}
		if (data->line[data->col] && data->line[data->col] != '\n')
			ft_parse_token(data);
	}
	if (data->line[data->col] == '\n')
	{
		if (ft_new_line_needed(&data->tokens))
		{
			ft_add_token(&data->tokens, ft_init_token(data, NULL,
						data->col, ENDLINE));
			data->col += 1;
		}
	}
	else if (ft_new_line_needed(&data->tokens))
		ft_exit_with_error(data, ERROR_NO_NEWLINE);
}

void		ft_parse_file(t_data *data)
{
	int	ret;

	while ((ret = ft_read_next_line(data, data->fd, &data->line)) > 0)
	{
		data->col = 0;
		ft_parse_line(data);
		data->row += 1;
		ft_strdel(&data->line);
	}
	if (ret == -1)
		ft_exit_with_error(data, ERROR_READ_FILE);
}
