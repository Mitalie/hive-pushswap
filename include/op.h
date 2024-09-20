/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:39:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/20 17:33:36 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include "status.h"
# include <stdbool.h>
# include <stddef.h>

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
	Buffer size must be at least the longest valid line including the newline
	character, but a larger buffer reduces the number of read system calls.
*/
# define OP_READ_BUF_SIZE 256

/*
	A struct to store the state of reading ops from a particular file
	descriptor. The fields should be considered private, but are defined here to
	allow stack allocation of the struct.
*/
typedef struct s_op_read_state
{
	char	buf[OP_READ_BUF_SIZE];
	int		fd;
	size_t	start;
	size_t	len;
}	t_op_read_state;

/*
	Initialize `t_op_read_state` for reading ops from a particular file
	descriptor.
*/
void		op_read_init(t_op_read_state *s, int fd);

/*
	Read next op from the file. If an op is successfully read and parsed, the op
	is written to `op` and false is written to `end`. If end of file has been
	reached and no more ops are available, true is written to `end`. If a read
	error occurs or invalid input is detected, an error code is returned
	instead.
*/
t_ps_status	op_read_next(t_op_read_state *s, bool *end, t_op *op);

/*
	Write the string representation of an op to the given file descriptor.
*/
t_ps_status	op_write(int fd, t_op op);

#endif
