/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:35:04 by cjosue            #+#    #+#             */
/*   Updated: 2020/02/03 15:35:06 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_op.h"
#include "dis_asm.h"

void				ft_del_data(t_data **data)
{
	if (!(*data))
		return ;
	ft_strdel((char**)&((*data)->file));
	ft_strdel((char**)&((*data)->name));
	ft_strdel((char**)&((*data)->command));
	if ((*data)->fd[0])
		close((*data)->fd[0]);
	if ((*data)->fd[1])
		close((*data)->fd[1]);
	free(*data);
}

char				*ft_create_file_name(char *av, t_data *data)
{
	char			*tmp;
	char			*tmp2;

	tmp2 = ft_strdup(av);
	if (!(tmp = ft_strrchr(tmp2, '.')))
		ft_error(data, ERROR_NOF);
	if (!tmp || ft_strcmp(tmp, FILE_EXT_IN))
		ft_error(data, ERROR_NOF);
	*tmp = '\0';
	tmp = tmp2;
	if (!(tmp2 = ft_strjoin(tmp2, FILE_EXT_OUT)))
		ft_error(data, ERROR_MALLOC);
	ft_strdel(&tmp);
	return (tmp2);
}

void				ft_read_cor(t_data *data, char *str)
{
	unsigned char	*tmp;
	size_t			size;

	data->fd[0] = open(str, O_RDONLY);
	if (data->fd[0] <= 0)
		ft_error(data, ERROR_BIN);
	if ((data->fd[1] = open(data->file, O_WRONLY | O_CREAT | O_TRUNC, 0666))
		== -1)
		ft_error(data, ERROR_BIN);
	size = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	if (!(data->name = ft_memalloc(size + 1)))
		ft_error(data, ERROR_MALLOC);
	if (read(data->fd[0], data->name, size) < (long int)size)
		ft_error(data, ERROR_NOF);
	if (ft_read_number(data->name + 4 + PROG_NAME_LENGTH, 4) != 0)
		ft_error(data, ERROR_BIN);
	if (ft_read_number(data->name + (size - 4), 4) != 0)
		ft_error(data, ERROR_BIN);
	size = ft_read_number(data->name + PROG_NAME_LENGTH + 8, 4);
	data->lenght = size;
	if (!((data->command) = ft_memalloc(size + 1)))
		ft_error(data, ERROR_MALLOC);
	tmp = data->command;
	while ((size = read(data->fd[0], tmp, MAX_BUFFER)) > 0)
		tmp = tmp + size;
}
