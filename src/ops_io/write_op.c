/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:31:40 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/09 16:40:00 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops_io.h"
#include <errno.h>
#include <unistd.h>

static bool	do_write(int fd, char *buf, size_t len)
{
	ssize_t	ret;

	while (len)
	{
		ret = write(fd, buf, len);
		if (ret < 0 && errno == EINTR)
			continue ;
		if (ret < 0)
			return (false);
		buf += ret;
		len -= ret;
	}
	return (true);
}

t_ps_status	write_op(int fd, t_ps_op op)
{
	const char	*op_str;
	char		buf[MAX_OP_LEN + 1];
	size_t		len;

	op_str = op_to_string(op);
	len = 0;
	while (op_str[len])
	{
		buf[len] = op_str[len];
		len++;
	}
	buf[len++] = '\n';
	if (!do_write(fd, buf, len))
		return (PS_ERR_WRITE_FAILURE);
	return (PS_SUCCESS);
}
