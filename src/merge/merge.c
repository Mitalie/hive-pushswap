/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:44:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/09 18:56:21 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"
#include "merge_internal.h"
#include <stdlib.h>
#include "runs.h"
#include "circ.h"

static void	prepare_merge(t_merge_state *s, t_stacks *stacks, t_runs *runs)
{
	int	runs_b;
	int	items_b;
	int	run;

	runs_b = runs->num_runs[B1] + runs->num_runs[B2];
	items_b = 0;
	while (runs_b--)
	{
		run = *circ_ptr(runs->b, runs_b);
		if (run < 0)
			items_b -= run;
		else
			items_b += run;
	}
	while (items_b--)
	{
		merge_op_queue_add(s, OP_PB);
		perform_op(stacks, OP_PB);
	}
}

/*
	OP_INVALID serves as end-of-array marker
*/
static const t_ps_op *const	g_ops_to_a[NUM_SOURCES] = {
	(const t_ps_op[]){OP_RRA, OP_INVALID},
	(const t_ps_op[]){OP_PA, OP_INVALID},
	(const t_ps_op[]){OP_RRB, OP_PA, OP_INVALID},
};
static const t_ps_op *const	g_ops_to_b[NUM_SOURCES] = {
	(const t_ps_op[]){OP_RRB, OP_INVALID},
	(const t_ps_op[]){OP_PB, OP_INVALID},
	(const t_ps_op[]){OP_RRA, OP_PB, OP_INVALID},
};

static void
	select_merge_stacks(t_merge_state *s, t_stacks *stacks, t_runs *runs)
{
	if (runs->current_loc == A1 || runs->current_loc == A2)
	{
		s->runs_curr = runs->a;
		s->runs_other = runs->b;
		s->data_curr = stacks->a;
		s->data_other = stacks->b;
		s->pushswap_ops = g_ops_to_a;
	}
	else
	{
		s->runs_curr = runs->b;
		s->runs_other = runs->a;
		s->data_curr = stacks->b;
		s->data_other = stacks->a;
		s->pushswap_ops = g_ops_to_b;
	}
}

static void	merge_pass(t_merge_state *s, t_stacks *stacks, t_runs *runs)
{
	int				pass_size;
	int				loc;

	runs->current_loc = (runs->current_loc + NUM_LOCS - 1) % NUM_LOCS;
	pass_size = runs->num_runs[(runs->current_loc + NUM_LOCS - 1) % NUM_LOCS];
	loc = 0;
	while (loc < NUM_LOCS)
		runs->num_runs[loc++] -= pass_size;
	runs->num_runs[runs->current_loc] = pass_size;
	runs->total_runs -= 2 * pass_size;
	select_merge_stacks(s, stacks, runs);
	while (pass_size--)
		merge_run(s);
}

t_ps_status	pushswap_merge(t_stacks *stacks, int num_items, int output_fd)
{
	t_runs			runs;
	t_ps_status		status;
	t_merge_state	s;

	status = calculate_runs(&runs, num_items);
	if (status == PS_SUCCESS)
	{
		s.stacks = stacks;
		s.output_fd = output_fd;
		s.output_queue_size = runs.total_runs;
		s.output_queue = circ_alloc(s.output_queue_size);
		if (!s.output_queue)
			status = PS_ERR_ALLOC_FAILURE;
		else
		{
			prepare_merge(&s, stacks, &runs);
			while (runs.total_runs > 1)
				merge_pass(&s, stacks, &runs);
			merge_op_queue_flush(&s);
			free(s.output_queue);
		}
	}
	free(runs.a);
	free(runs.b);
	return (status);
}
