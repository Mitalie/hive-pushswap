/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:32:43 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/30 16:05:08 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_internal.h"
#include <stdbool.h>

static int	peek(t_merge_state *s, t_merge_source src)
{
	if (src == CURR_BOT)
		return (circ_peek_front(s->data_curr));
	if (src == OTHER_TOP)
		return (circ_peek_back(s->data_other));
	return (circ_peek_front(s->data_other));
}

static int	pop(t_merge_state *s, t_merge_source src)
{
	s->run_items[src]--;
	if (src == CURR_BOT)
		return (circ_pop_front(s->data_curr));
	if (src == OTHER_TOP)
		return (circ_pop_back(s->data_other));
	return (circ_pop_front(s->data_other));
}

static bool	cmp(t_merge_state *s, t_merge_source a, t_merge_source b)
{
	if ((a == CURR_BOT && !s->run_items[CURR_BOT])
		|| (a == OTHER_TOP && !s->run_items[OTHER_TOP])
		|| (a == OTHER_BOT && !s->run_items[OTHER_BOT]))
		return (false);
	if ((b == CURR_BOT && !s->run_items[CURR_BOT])
		|| (b == OTHER_TOP && !s->run_items[OTHER_TOP])
		|| (b == OTHER_BOT && !s->run_items[OTHER_BOT]))
		return (true);
	if (s->run_dir < 0)
		return (peek(s, a) < peek(s, b));
	return (peek(s, a) > peek(s, b));
}

static void	perform_merge_ops(t_merge_state *s, t_merge_source src)
{
	const t_ps_op	*ops;

	ops = s->pushswap_ops[src];
	while (*ops != OP_INVALID)
		merge_output_op(s, *ops++);
	circ_push_back(s->data_curr, pop(s, src));
}

void	merge_run(t_merge_state *s)
{
	int	combined;
	int	dir;

	combined = circ_peek_front(s->runs_curr) - circ_peek_back(s->runs_other)
		+ circ_peek_front(s->runs_other);
	dir = 1;
	if (combined < 0)
		dir = -1;
	s->run_items[CURR_BOT] = dir * circ_pop_front(s->runs_curr);
	s->run_items[OTHER_TOP] = -dir * circ_pop_back(s->runs_other);
	s->run_items[OTHER_BOT] = dir * circ_pop_front(s->runs_other);
	circ_push_back(s->runs_curr, combined);
	s->run_dir = dir;
	combined *= dir;
	while (combined--)
	{
		if (cmp(s, CURR_BOT, OTHER_TOP) && cmp(s, CURR_BOT, OTHER_BOT))
			perform_merge_ops(s, CURR_BOT);
		else if (cmp(s, OTHER_TOP, OTHER_BOT))
			perform_merge_ops(s, OTHER_TOP);
		else
			perform_merge_ops(s, OTHER_BOT);
	}
}
