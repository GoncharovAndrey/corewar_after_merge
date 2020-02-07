/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dis_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 16:22:49 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/31 16:22:51 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_op.h"
#include "dis_asm.h"

static int			ft_find_com(unsigned char **tmp)
{
	int				res;

	res = 0;
	while (g_op_tab[res].code)
	{
		if (g_op_tab[res].code == **tmp)
		{
			(*tmp)++;
			return (res);
		}
		res++;
	}
	return (-1);
}

static void			ft_read_type(unsigned char **tmp, t_dcom *tk)
{
	int				i;

	i = 0;
	if (!g_op_tab[tk->name].args_types_mask)
	{
		while (g_op_tab[tk->name].args_types[i])
		{
			if (g_op_tab[tk->name].args_types[i] == T_REG)
				tk->type[i] = REG_CODE;
			else if (g_op_tab[tk->name].args_types[i] == T_IND)
				tk->type[i] = IND_CODE;
			else if (g_op_tab[tk->name].args_types[i] == T_DIR)
				tk->type[i] = DIR_CODE;
			i++;
		}
		return ;
	}
	while ((**tmp & (3 << (6 - (i * 2)))))
	{
		tk->type[i] = **tmp & (3 << (6 - (i * 2)));
		tk->type[i] >>= (6 - (i * 2));
		i++;
	}
	(*tmp)++;
}

static int			ft_value_arg(t_data *data, unsigned char **tmp,
					t_dcom *tk, int i)
{
	int				num;

	num = 0;
	if (tk->type[i] == REG_CODE)
	{
		num = (REG_TYPE)ft_read_number(*tmp, REG_BYTE);
		(*tmp) += REG_BYTE;
		write(data->fd[1], "r", 1);
	}
	if (tk->type[i] == IND_CODE)
	{
		num = (IND_TYPE)ft_read_number(*tmp, IND_SIZE);
		(*tmp) += IND_SIZE;
	}
	if (tk->type[i] == DIR_CODE)
	{
		if (g_op_tab[tk->name].t_dir_size == 2)
			num = (DIR_T2)ft_read_number(*tmp, g_op_tab[tk->name].t_dir_size);
		else
			num = (DIR_T4)ft_read_number(*tmp, g_op_tab[tk->name].t_dir_size);
		(*tmp) += g_op_tab[tk->name].t_dir_size;
		write(data->fd[1], "%", 1);
	}
	return (num);
}

static void			ft_write_arg(t_data *data, unsigned char **tmp, t_dcom *tk)
{
	int				i;
	int				num;

	i = 0;
	while (tk->type[i])
	{
		num = ft_value_arg(data, tmp, tk, i);
		ft_putnbr_fd(num, data->fd[1]);
		i++;
		if (tk->type[i])
			write(data->fd[1], ", ", 2);
	}
	write(data->fd[1], "\n", 1);
}

void				ft_dis_command(t_data *data)
{
	size_t			i;
	unsigned char	*tmp;
	t_dcom			token;

	i = 0;
	tmp = data->command;
	while (tmp < data->command + data->lenght)
	{
		ft_memset(&token, 0, sizeof(t_dcom));
		if ((token.name = ft_find_com(&tmp)) == -1)
			ft_error(data, ERROR_BIN);
		ft_putstr_fd(g_op_tab[token.name].name, data->fd[1]);
		ft_putchar_fd(32, data->fd[1]);
		ft_read_type(&tmp, &token);
		ft_write_arg(data, &tmp, &token);
	}
}
