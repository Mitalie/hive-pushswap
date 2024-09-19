/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:39:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/19 17:16:39 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPS_H
# define OPS_H

# include <stdbool.h>
# include <stddef.h>
# include "stacks.h"
# include "status.h"

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

/*
	Buffer size must be at least the longest valid line including the newline
	character, but a larger buffer reduces the number of read system calls.
*/
# define READ_OPS_BUF_SIZE 256

/*
	A struct to store the state of reading ops from a particular file
	descriptor. The fields should be considered private, but are defined here to
	allow stack allocation of the struct.
*/
typedef struct s_read_ops_state
{
	char	buf[READ_OPS_BUF_SIZE];
	int		fd;
	size_t	start;
	size_t	len;
}	t_read_ops_state;

/*
	Initialize `t_read_ops_state` for reading ops from a particular file
	descriptor.
*/
void		read_ops_init(t_read_ops_state *s, int fd);

/*
	Read next op from the file. If an op is successfully read and parsed, the op
	is written to `op` and false is written to `end`. If end of file has been
	reached and no more ops are available, true is written to `end`. If a read
	error occurs or invalid input is detected, an error code is returned
	instead.
*/
t_ps_status	read_ops_next(t_read_ops_state *s, bool *end, t_ps_op *op);

/*
	Write the string representation of an op to the given file descriptor.
*/
t_ps_status	write_op(int fd, t_ps_op op);

#endif
