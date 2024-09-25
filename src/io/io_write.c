/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:37:19 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/25 15:44:43 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

#include <errno.h>
#include <unistd.h>

t_ps_status	io_write(int fd, char *buf, size_t len)
{
	ssize_t	ret;

	while (len)
	{
		ret = write(fd, buf, len);
		if (ret < 0 && errno == EINTR)
			continue ;
		if (ret < 0)
			return (PS_ERR_WRITE_FAILURE);
		buf += ret;
		len -= ret;
	}
	return (PS_SUCCESS);
}
