/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ops.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:22:04 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/22 20:27:06 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_OPS_H
# define READ_OPS_H

# include <stdbool.h>
# include <stddef.h>
# include "status.h"
# include "ops.h"

# define READ_OPS_BUF_SIZE 256

typedef struct s_read_ops_state
{
	char	buf[READ_OPS_BUF_SIZE];
	int		fd;
	size_t	start;
	size_t	len;
}	t_read_ops_state;

void		read_ops_init(t_read_ops_state *s, int fd);
t_ps_status	read_ops_next(t_read_ops_state *s, bool *end, t_ps_op *op);

#endif
