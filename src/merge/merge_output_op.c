/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_output_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:20:06 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/30 16:05:07 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_internal.h"
#include <stdbool.h>
#include <stdio.h>

static bool	cancel(t_merge_state *s, t_ps_op op)
{
	if (!circ_len(s->output_queue))
		return (false);
	if ((op == OP_PA && circ_peek_front(s->output_queue) == OP_PB)
		|| (op == OP_PB && circ_peek_front(s->output_queue) == OP_PA))
	{
		circ_pop_front(s->output_queue);
		return (true);
	}
	return (false);
}

static bool	combine(t_merge_state *s, t_ps_op op)
{
	if (!circ_len(s->output_queue))
		return (false);
	if ((op == OP_RRA && circ_peek_front(s->output_queue) == OP_RRB)
		|| (op == OP_RRB && circ_peek_front(s->output_queue) == OP_RRA))
	{
		circ_pop_front(s->output_queue);
		circ_push_front(s->output_queue, OP_RRR);
		return (true);
	}
	return (false);
}

static bool	noop(t_merge_state *s, t_ps_op op)
{
	if ((op == OP_RRA && circ_len(s->stacks->a) <= 1)
		|| (op == OP_RRB && circ_len(s->stacks->b) <= 1))
	{
		return (true);
	}
	return (false);
}

void	merge_output_op(t_merge_state *s, t_ps_op op)
{
	if (op == OP_INVALID)
	{
		while (circ_len(s->output_queue))
			printf("%s\n", op_to_string(circ_pop_back(s->output_queue)));
		return ;
	}
	if (noop(s, op))
		return ;
	if (cancel(s, op))
		return ;
	if (combine(s, op))
		return ;
	if (circ_len(s->output_queue) == s->output_queue_size)
		printf("%s\n", op_to_string(circ_pop_back(s->output_queue)));
	circ_push_front(s->output_queue, op);
}
