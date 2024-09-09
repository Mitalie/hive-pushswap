/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_op_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:17:52 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/09 17:32:04 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_internal.h"
#include "circ.h"
#include "ops_io.h"

void	merge_op_queue_flush(t_merge_state *s)
{
	while (circ_len(s->output_queue))
		write_op(s->output_fd, circ_pop_back(s->output_queue));
}

void	merge_op_queue_add(t_merge_state *s, t_ps_op op)
{
	if (circ_len(s->output_queue) == s->output_queue_size)
		write_op(s->output_fd, circ_pop_back(s->output_queue));
	circ_push_front(s->output_queue, op);
}
