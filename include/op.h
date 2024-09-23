/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:39:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/23 16:52:15 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include "status.h"

typedef struct s_stacks	t_stacks;

// The enum values must match the lookup table indices in op_util.c!

typedef enum e_op
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
}	t_op;

// Longest op strings are 3 characters
# define OP_MAX_LEN 3

void		op_execute(t_stacks *stacks, t_op op);
const char	*op_to_string(t_op op);
t_op		op_from_string(const char *str);
t_op		op_reverse(t_op op);

/*
	Write the string representation of an op to the given file descriptor.
*/
t_ps_status	op_write(int fd, t_op op);

#endif
