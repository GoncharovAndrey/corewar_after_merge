/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:31:50 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/02 15:38:50 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_set_next_line(t_data *data, char **line)
{
	char	*end_line;
	char	*str_tmp;

	if (!(end_line = ft_strchr(data->buff_line, '\n')))
	{
		*line = ft_strdup(data->buff_line);
		ft_strdel(&data->buff_line);
	}
	else
	{
		end_line += 1;
		*line = ft_strndup(data->buff_line,
						(size_t)(end_line - data->buff_line));
		if (!(str_tmp = ft_strdup(end_line)))
			return (-1);
		free(data->buff_line);
		data->buff_line = str_tmp;
	}
	if (!(*line))
		return (-1);
	return (1);
}

int			ft_read_next_line(t_data *data, const int fd, char **line)
{
	char	*str_tmp;
	char	buffer[BUFF_SIZE + 1];
	int		nbytes;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!data->buff_line)
		data->buff_line = ft_strnew(0);
	while ((nbytes = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[nbytes] = '\0';
		if (!(str_tmp = ft_strjoin(data->buff_line, buffer)))
			return (-1);
		free(data->buff_line);
		data->buff_line = str_tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (nbytes == 0 && (!data->buff_line || !data->buff_line[0]))
		return (0);
	if (nbytes < 0)
		return (-1);
	return (ft_set_next_line(data, line));
}

void		ft_read_till_quote(t_data *data)
{
	int		ret;
	char	*new_line;
	char	*tmp_line;

	while (!ft_strchr(data->line + data->col, '"'))
	{
		while (data->line[data->col] && data->line[data->col] != '\n')
			data->col += 1;
		data->col += 1;
		data->row += 1;
		if ((ret = ft_read_next_line(data, data->fd, &new_line)) <= 0)
			ft_exit_with_lexical_error(data, data->col + 1);
		tmp_line = data->line;
		if (!(data->line = ft_strjoin(tmp_line, new_line)))
			ft_exit_with_error(data, ERROR_MALLOC);
		ft_strdel(&tmp_line);
		ft_strdel(&new_line);
	}
}
