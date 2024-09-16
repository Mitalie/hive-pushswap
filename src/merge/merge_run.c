/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:32:43 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/16 15:58:00 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_internal.h"
#include <stdbool.h>

static int	peek(t_merge_pass_state *pass, t_merge_source src)
{
	if (src == CURR_BOT)
		return (circ_peek_front(pass->data_curr));
	if (src == OTHER_TOP)
		return (circ_peek_back(pass->data_other));
	return (circ_peek_front(pass->data_other));
}

static bool	cmp(t_merge_pass_state *pass, t_merge_run_state *run,
	t_merge_source a, t_merge_source b)
{
	if (!run->run_items[a])
		return (false);
	if (!run->run_items[b])
		return (true);
	if (run->run_dir < 0)
		return (peek(pass, a) < peek(pass, b));
	return (peek(pass, a) > peek(pass, b));
}

static void	merge_one_item(t_merge_state *merge, t_merge_pass_state *pass,
	t_merge_run_state *run)
{
	t_merge_source	src;
	const t_ps_op	*ops;

	if (cmp(pass, run, CURR_BOT, OTHER_TOP)
		&& cmp(pass, run, CURR_BOT, OTHER_BOT))
		src = CURR_BOT;
	else if (cmp(pass, run, OTHER_TOP, OTHER_BOT))
		src = OTHER_TOP;
	else
		src = OTHER_BOT;
	ops = pass->pushswap_ops[src];
	while (*ops != OP_INVALID)
	{
		merge_op_queue_add(merge, *ops);
		perform_op(merge->stacks, *ops);
		ops++;
	}
	run->run_items[src]--;
}

void	merge_run(t_merge_state *merge, t_merge_pass_state *pass)
{
	t_merge_run_state	run;
	int					combined;
	int					dir;

	combined = circ_peek_front(pass->runs_curr)
		- circ_peek_back(pass->runs_other)
		+ circ_peek_front(pass->runs_other);
	dir = 1;
	if (combined < 0)
		dir = -1;
	run.run_items[CURR_BOT] = dir * circ_pop_front(pass->runs_curr);
	run.run_items[OTHER_TOP] = -dir * circ_pop_back(pass->runs_other);
	run.run_items[OTHER_BOT] = dir * circ_pop_front(pass->runs_other);
	circ_push_back(pass->runs_curr, combined);
	run.run_dir = dir;
	combined *= dir;
	while (combined--)
		merge_one_item(merge, pass, &run);
}
