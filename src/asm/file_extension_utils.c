/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extension_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 20:51:34 by jgoyette          #+#    #+#             */
/*   Updated: 2020/01/31 20:54:35 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_has_extension(const char *filename, const char *extension)
{
	int filename_len;
	int extension_len;

	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	return (filename_len >= extension_len &&
			ft_strequ(filename + (filename_len - extension_len), extension));
}

char	*ft_remove_extension(t_data *data, const char *filename,
		const char *extension)
{
	int		result_filename_len;
	char	*result_filename;

	result_filename_len = (ft_strlen(filename) - ft_strlen(extension));
	if (!(result_filename = ft_strsub(filename, 0, result_filename_len)))
		ft_exit_with_error(data, ERROR_MALLOC);
	return (result_filename);
}
