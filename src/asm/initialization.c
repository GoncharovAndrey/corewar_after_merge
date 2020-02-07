/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:19:05 by jgoyette          #+#    #+#             */
/*   Updated: 2020/01/31 21:19:20 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_data	*ft_init_data(char *filename)
{
	t_data *data;

	if (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
		ft_exit_with_error(data, ERROR_MALLOC);
	if ((data->fd = open(filename, O_RDONLY)) == -1)
		ft_exit_with_io_error(data, "Can't read source file", filename);
	data->filename = ft_remove_extension(data, filename, ".s");
	return (data);
}

t_token	*ft_init_token(t_data *data, char *content, int start, t_type type)
{
	t_token *token;

	if (!(token = (t_token *)ft_memalloc(sizeof(t_token))))
		ft_exit_with_error(data, ERROR_MALLOC);
	token->content = content;
	token->type = type;
	token->row = data->row;
	token->col = start;
	token->next = NULL;
	return (token);
}

t_token	*ft_init_label(t_data *data, char *content, int pos)
{
	t_token *label;

	if (!(label = (t_token *)ft_memalloc(sizeof(t_token))))
		ft_exit_with_error(data, ERROR_MALLOC);
	label->content = content;
	label->pos = pos;
	label->next = NULL;
	return (label);
}
