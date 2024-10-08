/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:31:40 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/25 15:44:38 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

#include "io.h"
#include <stddef.h>

t_ps_status	op_write(int fd, t_op op)
{
	const char	*op_str;
	char		buf[OP_MAX_LEN + 1];
	size_t		len;

	op_str = op_to_string(op);
	len = 0;
	while (op_str[len])
	{
		buf[len] = op_str[len];
		len++;
	}
	buf[len++] = '\n';
	return (io_write(fd, buf, len));
}
