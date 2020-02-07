/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:08:47 by jgoyette          #+#    #+#             */
/*   Updated: 2020/01/31 21:09:52 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_parse_command(t_data *data, char *line)
{
	int		start;
	t_type	type;

	start = data->col;
	data->col += 1;
	while (line[data->col] && (ft_strchr(NAME_CMD_STRING, line[data->col])
				|| ft_strchr(COMMENT_CMD_STRING, line[data->col])))
		data->col += 1;
	if (!(data->content = ft_strsub(line, start, data->col - start)))
		ft_exit_with_error(data, ERROR_MALLOC);
	if (!ft_strequ(data->content, COMMENT_CMD_STRING)
			&& !ft_strequ(data->content, NAME_CMD_STRING))
		ft_exit_with_lexical_error(data, start + 1);
	while (ft_isspace(line[data->col]))
		data->col += 1;
	if (line[data->col] != '"')
		ft_exit_with_lexical_error(data, data->col + 1);
	if (ft_strequ(data->content, NAME_CMD_STRING))
		type = COMMAND_NAME;
	else
		type = COMMAND_COMMENT;
	ft_add_token(&data->tokens, ft_init_token(data, data->content,
														start, type));
	data->content = NULL;
}

void	ft_parse_string(t_data *data)
{
	int		start;

	data->col += 1;
	start = data->col;
	if (!ft_strchr(data->line + data->col, '"'))
		ft_read_till_quote(data);
	while (data->line[data->col] && data->line[data->col] != '"')
		data->col += 1;
	if (!(data->content = ft_strsub(data->line, start, data->col - start)))
		ft_exit_with_error(data, ERROR_MALLOC);
	data->col += 1;
	ft_add_token(&data->tokens, ft_init_token(data, data->content,
													start - 1, STRING));
	data->content = NULL;
}

void	ft_parse_direct(t_data *data, char *line)
{
	int		start;
	t_type	type;

	start = data->col;
	if (line[++data->col] == LABEL_CHAR && ++data->col)
	{
		if ((type = DIRECT_LABEL) && !ft_strchr(LABEL_CHARS, line[data->col]))
			ft_exit_with_lexical_error(data, start + 1);
		while (line[data->col] && ft_strchr(LABEL_CHARS, line[data->col]))
			data->col += 1;
	}
	else
	{
		if ((type = DIRECT_NUM) && line[data->col] == '-')
			data->col += 1;
		if (!ft_isdigit(line[data->col]))
			ft_exit_with_lexical_error(data, start + 1);
		while (line[data->col] && ft_isdigit(line[data->col]))
			data->col += 1;
	}
	if (!(data->content = ft_strsub(line, start, data->col - start)))
		ft_exit_with_error(data, ERROR_MALLOC);
	ft_add_token(&data->tokens, ft_init_token(data, data->content,
														start, type));
	data->content = NULL;
}

void	ft_parse_alpha(t_data *data, char *line)
{
	int		start;
	t_type	type;

	start = data->col;
	type = INSTRUCTION;
	if (line[data->col] == LABEL_CHAR && (type = INDIRECT_LABEL))
		data->col += 1;
	if (!line[data->col] || !ft_strchr(LABEL_CHARS, line[data->col]))
		ft_exit_with_lexical_error(data, start + 1);
	while (line[data->col] && ft_strchr(LABEL_CHARS, line[data->col]))
		data->col += 1;
	if (line[data->col] == LABEL_CHAR && (type = LABEL))
		data->col += 1;
	if (!(data->content = ft_strsub(data->line, start, data->col - start)))
		ft_exit_with_error(data, ERROR_MALLOC);
	if (ft_is_register(data->content))
		type = REGISTER;
	ft_add_token(&data->tokens, ft_init_token(data, data->content,
														start, type));
	data->content = NULL;
}

void	ft_parse_num(t_data *data, char *line)
{
	int		start;
	t_type	type;

	start = data->col;
	type = INDIRECT_NUM;
	if (line[data->col] == '+')
		ft_exit_with_lexical_error(data, start + 1);
	if (line[data->col] == '-')
		data->col += 1;
	while (line[data->col] && ft_strchr(LABEL_CHARS, line[data->col]))
	{
		if (!ft_isdigit(line[data->col]))
			type = LABEL;
		data->col += 1;
	}
	if (line[data->col] == LABEL_CHAR && line[start] != '-' && (type = LABEL))
		data->col += 1;
	else if ((line[data->col] == LABEL_CHAR && line[start] == '-')
													|| type == LABEL)
		ft_exit_with_lexical_error(data, start + 1);
	if (!(data->content = ft_strsub(line, start, data->col - start)))
		ft_exit_with_error(data, ERROR_MALLOC);
	ft_add_token(&data->tokens, ft_init_token(data, data->content,
														start, type));
	data->content = NULL;
}
