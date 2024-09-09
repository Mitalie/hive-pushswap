/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_op_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:17:52 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/09 18:35:05 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_internal.h"
#include <stdbool.h>
#include "circ.h"
#include "ops_io.h"

/*
	If stack doesn't have at least two items, rotations do nothing and can be
	omitted from the output.

	There are other no-op situations, but these are the only ones our merge sort
	algorithm can produce.
*/
static bool	noop(t_merge_state *s, t_ps_op op)
{
	if (op == OP_RRA && circ_len(s->stacks->a) < 2)
		return (true);
	if (op == OP_RRB && circ_len(s->stacks->b) < 2)
		return (true);
	return (false);
}

/*
	If current and previous op cancel out, remove both.

	There are other cancelling pairs, but these are the only ones our merge sort
	algorithm can produce.
*/
static bool	cancel(t_merge_state *s, t_ps_op op)
{
	t_ps_op	prev;

	if (!circ_len(s->output_queue))
		return (false);
	prev = circ_peek_front(s->output_queue);
	if ((op == OP_PA && prev == OP_PB)
		|| (op == OP_PB && prev == OP_PA))
	{
		circ_pop_front(s->output_queue);
		return (true);
	}
	return (false);
}

/*
	If current and previous ops can be combined into one that operates on both
	stacks, do so.

	There are other combining pairs, but these are the only ones our merge sort
	algorithm can produce. This doesn't handle longer combining groups, but we
	don't produce those either.
*/
static bool	combine(t_merge_state *s, t_ps_op op)
{
	t_ps_op	prev;

	if (!circ_len(s->output_queue))
		return (false);
	prev = circ_peek_front(s->output_queue);
	if ((op == OP_RRA && prev == OP_RRB)
		|| (op == OP_RRB && prev == OP_RRA))
	{
		*circ_ptr(s->output_queue, 0) = OP_RRR;
		return (true);
	}
	return (false);
}

/*
	Add an op to the queue. If it matches one of the special cases that allow
	omitting or merging, apply that instead. If the queue would overflow, oldest
	queued op is written out.
*/
void	merge_op_queue_add(t_merge_state *s, t_ps_op op)
{
	if (noop(s, op))
		return ;
	if (cancel(s, op))
		return ;
	if (combine(s, op))
		return ;
	if (circ_len(s->output_queue) == s->output_queue_size)
		write_op(s->output_fd, circ_pop_back(s->output_queue));
	circ_push_front(s->output_queue, op);
}

/*
	Write out all the operations in the queue, emptying it.
*/
void	merge_op_queue_flush(t_merge_state *s)
{
	while (circ_len(s->output_queue))
		write_op(s->output_fd, circ_pop_back(s->output_queue));
}
