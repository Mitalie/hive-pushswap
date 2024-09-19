/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_io.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:22:04 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/19 13:44:11 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPS_IO_H
# define OPS_IO_H

# include <stdbool.h>
# include <stddef.h>
# include "status.h"
# include "ops.h"

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
