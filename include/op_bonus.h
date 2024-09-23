/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bonus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:51:29 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/23 16:54:24 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_BONUS_H
# define OP_BONUS_H

# include "op.h"
# include "status.h"
# include <stdbool.h>
# include <stddef.h>

/*
	These definitions are split from op.h because they're only used in the bonus
	part of the assignment.
*/

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

#endif
