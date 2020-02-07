/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 20:42:00 by jgoyette          #+#    #+#             */
/*   Updated: 2020/01/31 20:42:40 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_clean_token_content(t_token **token)
{
	if (token && *token)
	{
		ft_strdel(&(*token)->content);
		free(*token);
		*token = NULL;
	}
}

static void	ft_clean_tokens(t_token **tokens)
{
	t_token	*tmp;

	if (tokens && *tokens)
	{
		while (*tokens)
		{
			tmp = *tokens;
			*tokens = (*tokens)->next;
			ft_clean_token_content(&tmp);
			tmp = NULL;
		}
		ft_memdel((void **)tokens);
	}
}

static void	ft_clean_labels(t_token **labels)
{
	t_token	*tmp;

	if (labels && *labels)
	{
		while (*labels)
		{
			tmp = *labels;
			*labels = (*labels)->next;
			free(tmp);
			tmp = NULL;
		}
		ft_memdel((void **)labels);
	}
}

void		ft_clean_data(t_data *data)
{
	if (data)
	{
		ft_strdel(&data->filename);
		ft_strdel(&data->line);
		ft_strdel(&data->buff_line);
		ft_strdel(&data->content);
		ft_clean_tokens(&data->tokens);
		ft_clean_labels(&data->labels);
		close(data->fd);
		ft_memdel((void **)&data);
	}
}
