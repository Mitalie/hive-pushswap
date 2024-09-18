/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:39:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/18 17:57:27 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPS_H
# define OPS_H

# include "stacks.h"

// The enum values must match the lookup table indices in ops_util.c!

typedef enum e_ps_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	NUM_OPS,
	OP_INVALID = -1,
}	t_ps_op;

// Longest op strings are 3 characters
# define MAX_OP_LEN 3

void		perform_op(t_stacks *stacks, t_ps_op op);
const char	*op_to_string(t_ps_op op);
t_ps_op		op_from_string(const char *str);
t_ps_op		op_reverse(t_ps_op op);

#endif
