/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_read_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:29:51 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/25 17:07:57 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_bonus.h"

#include <unistd.h>

/*
	Try to refill the buffer from input file if it's below the given minimum.
	The minimum ensures any valid line at the start of the buffer is fully read,
	while avoiding excessive buffer shifts and small reads.
*/
static bool	fill_buffer(t_op_read_state *s, size_t min_length)
{
	size_t	i;
	ssize_t	ret;

	if (s->len >= min_length)
		return (true);
	i = 0;
	while (i < s->len)
	{
		s->buf[i] = s->buf[s->start + i];
		i++;
	}
	s->start = 0;
	while (s->len < min_length)
	{
		ret = read(s->fd, s->buf + s->len, sizeof(s->buf) - s->len);
		if (ret < 0)
			return (false);
		if (ret == 0)
			break ;
		s->len += ret;
	}
	return (true);
}

/*
	Cut a line from the buffer by replacing the first newline character with a
	null terminator and adjusting the buffer parameters accordingly. If there is
	no newline character in the buffer, the line is either too long or lacks a
	terminating newline, and a null pointer is returned.
*/
static char	*cut_line(t_op_read_state *s)
{
	char	*line;
	size_t	i;

	line = s->buf + s->start;
	i = 0;
	while (i < s->len)
	{
		if (s->buf[s->start + i] == '\n')
		{
			s->buf[s->start + i] = 0;
			s->start += i + 1;
			s->len -= i + 1;
			return (line);
		}
		i++;
	}
	return (0);
}

t_ps_status	op_read_next(t_op_read_state *s, bool *end, t_op *op)
{
	char	*line;

	if (!fill_buffer(s, OP_MAX_LEN + 1))
		return (PS_ERR_READ_FAILURE);
	*end = (s->len == 0);
	if (*end)
		return (PS_SUCCESS);
	line = cut_line(s);
	if (!line)
		return (PS_ERR_INPUT_OP_INVALID);
	*op = op_from_string(line);
	if (*op == OP_INVALID)
		return (PS_ERR_INPUT_OP_INVALID);
	return (PS_SUCCESS);
}

void	op_read_init(t_op_read_state *s, int fd)
{
	s->fd = fd;
	s->len = 0;
	s->start = 0;
}
