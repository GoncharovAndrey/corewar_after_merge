/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting_with_positional_error.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 20:48:25 by jgoyette          #+#    #+#             */
/*   Updated: 2020/01/31 20:50:58 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static const char	*ft_get_token_type(t_type type)
{
	if (type == ENDLINE)
		return ("ENDLINE");
	else if (type == COMMAND_NAME)
		return ("COMMAND_NAME");
	else if (type == COMMAND_COMMENT)
		return ("COMMAND_COMMENT");
	else if (type == STRING)
		return ("STRING");
	else if (type == SEPARATOR)
		return ("SEPARATOR");
	else if (type == INSTRUCTION)
		return ("INSTRUCTION");
	else if (type == LABEL)
		return ("LABEL");
	else if (type == REGISTER)
		return ("REGISTER");
	else if (type == DIRECT_LABEL)
		return ("DIRECT_LABEL");
	else if (type == INDIRECT_LABEL)
		return ("INDIRECT_LABEL");
	else if (type == DIRECT_NUM)
		return ("DIRECT_NUM");
	else if (type == INDIRECT_NUM)
		return ("INDIRECT_NUM");
	return ("UNKNOWN");
}

void				ft_exit_with_syntax_error(t_data *data)
{
	const char	*token_type;

	token_type = ft_get_token_type(data->curr_token->type);
	ft_dprintf(STDERR_FILENO, "Syntax error at token [TOKEN][%03d:%03d]" \
			" %s", data->curr_token->row + 1, data->curr_token->col + 1,
			token_type);
	if (data->curr_token->content)
		ft_dprintf(STDERR_FILENO, " \"%s\"\n", data->curr_token->content);
	else
		ft_dprintf(STDERR_FILENO, "\n");
	ft_clean_data(data);
	exit(EXIT_FAILURE);
}

void				ft_exit_with_invalid_instruction_error(t_data *data)
{
	const char	*token_type;

	token_type = ft_get_token_type(data->curr_token->type);
	ft_dprintf(STDERR_FILENO,
			"Invalid instruction at token [TOKEN][%03d:%03d] %s",
			data->curr_token->row + 1, data->curr_token->col + 1, token_type);
	if (data->curr_token->content)
		ft_dprintf(STDERR_FILENO, " \"%s\"\n", data->curr_token->content);
	else
		ft_dprintf(STDERR_FILENO, "\n");
	ft_clean_data(data);
	exit(EXIT_FAILURE);
}

void				ft_exit_with_no_such_label_error(t_data *data,
														t_token *token)
{
	const char	*token_type;

	token_type = ft_get_token_type(token->type);
	ft_dprintf(STDERR_FILENO, "No such label %s while attempting to " \
		"dereference token [TOKEN][%03d:%03d] %s \"%s\"\n", token->content,
		token->row + 1, token->col + 1, token_type, token->content);
	ft_clean_data(data);
	exit(EXIT_FAILURE);
}

void				ft_exit_with_lexical_error(t_data *data, int col)
{
	ft_dprintf(STDERR_FILENO, "Lexical error at [%d:%d]\n",
			data->row + 1, col);
	ft_clean_data(data);
	exit(EXIT_FAILURE);
}
