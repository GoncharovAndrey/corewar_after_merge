/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 07:21:23 by jgoyette          #+#    #+#             */
/*   Updated: 2019/10/11 17:32:06 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_set_line(int fd, char **fd_tab, char **line)
{
	char	*end_line;
	char	*str_tmp;

	if (!(end_line = ft_strchr(fd_tab[fd], '\n')))
	{
		*line = ft_strdup(fd_tab[fd]);
		ft_strdel(&fd_tab[fd]);
	}
	else
	{
		*line = ft_strndup(fd_tab[fd], (size_t)(end_line - fd_tab[fd]));
		if (!(str_tmp = ft_strdup(end_line + 1)))
			return (-1);
		free(fd_tab[fd]);
		fd_tab[fd] = str_tmp;
	}
	if (!(*line))
		return (-1);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*fd_tab[FD_MAX];
	char		*str_tmp;
	char		buffer[BUFF_SIZE + 1];
	int			nbytes;

	if (fd < 0 || fd > FD_MAX || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!fd_tab[fd])
		fd_tab[fd] = ft_strnew(0);
	while ((nbytes = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[nbytes] = '\0';
		if (!(str_tmp = ft_strjoin(fd_tab[fd], buffer)))
			return (-1);
		free(fd_tab[fd]);
		fd_tab[fd] = str_tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (nbytes < 0)
		return (-1);
	else if (nbytes == 0 && (!fd_tab[fd] || !fd_tab[fd][0]))
		return (0);
	return (ft_set_line(fd, fd_tab, line));
}
