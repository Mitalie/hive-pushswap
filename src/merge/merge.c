/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:44:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/19 17:41:13 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"
#include "merge_internal.h"
#include <stdlib.h>
#include "circ.h"

static t_ps_status	prepare_merge(
	t_merge_state *merge, t_stacks *stacks, t_runs *runs)
{
	int			runs_b;
	int			items_b;
	int			run;
	t_ps_status	status;

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
		status = merge_op_queue_add(merge, OP_PB);
		if (status != PS_SUCCESS)
			return (status);
		op_execute(stacks, OP_PB);
	}
	return (PS_SUCCESS);
}

/*
	OP_INVALID serves as end-of-array marker
*/
static const t_op *const	g_ops_to_a[NUM_SOURCES] = {
	(const t_op[]){OP_RRA, OP_INVALID},
	(const t_op[]){OP_PA, OP_INVALID},
	(const t_op[]){OP_RRB, OP_PA, OP_INVALID},
};
static const t_op *const	g_ops_to_b[NUM_SOURCES] = {
	(const t_op[]){OP_RRB, OP_INVALID},
	(const t_op[]){OP_PB, OP_INVALID},
	(const t_op[]){OP_RRA, OP_PB, OP_INVALID},
};

static void	select_merge_stacks(
	t_merge_pass_state *pass, t_stacks *stacks, t_runs *runs)
{
	if (runs->current_loc == A1 || runs->current_loc == A2)
	{
		pass->runs_curr = runs->a;
		pass->runs_other = runs->b;
		pass->data_curr = stacks->a;
		pass->data_other = stacks->b;
		pass->pushswap_ops = g_ops_to_a;
	}
	else
	{
		pass->runs_curr = runs->b;
		pass->runs_other = runs->a;
		pass->data_curr = stacks->b;
		pass->data_other = stacks->a;
		pass->pushswap_ops = g_ops_to_b;
	}
}

static void	merge_pass(t_merge_state *merge, t_stacks *stacks, t_runs *runs)
{
	int					pass_size;
	int					loc;
	t_merge_pass_state	pass;

	runs->current_loc = (runs->current_loc + NUM_LOCS - 1) % NUM_LOCS;
	pass_size = runs->num_runs[(runs->current_loc + NUM_LOCS - 1) % NUM_LOCS];
	loc = 0;
	while (loc < NUM_LOCS)
		runs->num_runs[loc++] -= pass_size;
	runs->num_runs[runs->current_loc] = pass_size;
	runs->total_runs -= 2 * pass_size;
	select_merge_stacks(&pass, stacks, runs);
	while (pass_size--)
		merge_run(merge, &pass);
}

t_ps_status	pushswap_merge(t_stacks *stacks, int num_items, int output_fd)
{
	t_runs			runs;
	t_ps_status		status;
	t_merge_state	merge;

	status = merge_runs_generate(&runs, num_items);
	merge.stacks = stacks;
	merge.output_fd = output_fd;
	merge.output_queue_size = runs.total_runs;
	merge.output_queue = 0;
	if (status == PS_SUCCESS)
		merge.output_queue = circ_alloc(merge.output_queue_size);
	if (status == PS_SUCCESS && !merge.output_queue)
		status = PS_ERR_ALLOC_FAILURE;
	if (status == PS_SUCCESS)
		status = prepare_merge(&merge, stacks, &runs);
	if (status == PS_SUCCESS)
		while (runs.total_runs > 1)
			merge_pass(&merge, stacks, &runs);
	if (status == PS_SUCCESS)
		status = merge_op_queue_flush(&merge);
	free(merge.output_queue);
	merge_runs_release(&runs);
	return (status);
}
