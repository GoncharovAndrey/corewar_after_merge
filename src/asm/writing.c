/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:53:38 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/04 17:45:57 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_write_bytecode(char *bytecode, unsigned int value, int size)
{
	int	i;

	i = 0;
	while (size)
	{
		bytecode[size - 1] = (value >> i) & 0xFF;
		i += 8;
		size -= 1;
	}
}

static void	ft_write_info(t_data *data, char **bytecode)
{
	ft_write_bytecode(*bytecode, COREWAR_EXEC_MAGIC, 4);
	*bytecode += 4;
	ft_memcpy(*bytecode, data->champion_name, ft_strlen(data->champion_name));
	*bytecode += PROG_NAME_LENGTH;
	*bytecode += 4;
	ft_write_bytecode(*bytecode, data->champion_code_size, 4);
	*bytecode += 4;
	ft_memcpy(*bytecode, data->champion_comment,
			ft_strlen(data->champion_comment));
	*bytecode += COMMENT_LENGTH;
	*bytecode += 4;
}

static void	ft_write_champion_code(t_data *data, char **bytecode)
{
	t_token			*token;
	unsigned int	value;

	token = data->start_code_token;
	while (token)
	{
		if (token->size > 0)
		{
			value = (unsigned int)token->value;
			if (token->size == 2)
				value &= 0xffff;
			ft_write_bytecode(*bytecode, value, token->size);
		}
		*bytecode += token->size;
		token = token->next;
	}
}

void		ft_write_to_file(t_data *data)
{
	int		fd;
	char	*filename;
	int		bytocode_len;
	char	*bytecode;
	char	*tmp;

	if (!(filename = ft_strjoin(data->filename, ".cor")))
		ft_exit_with_error(data, ERROR_MALLOC);
	if ((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		ft_exit_with_io_error(data, "Can't create file", filename);
	bytocode_len = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 +
		data->champion_code_size;
	if (!(bytecode = (char *)ft_memalloc(sizeof(char) * bytocode_len)))
		ft_exit_with_error(data, ERROR_MALLOC);
	tmp = bytecode;
	ft_write_info(data, &tmp);
	ft_write_champion_code(data, &tmp);
	ft_printf("Writing output program to %s\n", filename);
	write(fd, bytecode, bytocode_len);
	ft_strdel(&bytecode);
	ft_strdel(&filename);
	close(fd);
}
