/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_op.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:24:58 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/02 15:56:05 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_OP_H
# define ASM_OP_H

# include "op.h"

typedef struct		s_op
{
	const char		*name;
	int				nargs;
	int				args_types[3];
	int				code;
	int				args_types_mask;
	int				t_dir_size;
}					t_op;

static t_op		g_op_tab[19] =
{
	{"live", 1, {T_DIR}, 1, 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 1, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 1, 4},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 1, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 1, 4},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 1, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 1, 4},
	{"zjmp", 1, {T_DIR}, 9, 0, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 1, 2},
	{"fork", 1, {T_DIR}, 12, 0, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 1, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 1, 2},
	{"lfork", 1, {T_DIR}, 15, 0, 2},
	{"aff", 1, {T_REG}, 16, 1, 4},
	{"fastfork", 1, {T_DIR}, 17, 0, 2},
	{"trap", 1, {T_DIR}, 18, 0, 4},
	{ 0,0,{0},0,0,0}
};

#endif
