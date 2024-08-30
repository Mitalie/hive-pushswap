/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:44:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/30 14:11:22 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circ.h"
#include "merge.h"
#include "merge_internal.h"

static void	prepare_merge(t_stacks *stacks, t_runs *runs)
{
	int	i;
	int	runs_b;
	int	run;
	int	first;
	int	second;

	runs_b = runs->num_runs[B1] + runs->num_runs[B2];
	i = 0;
	while (i < runs_b)
	{
		run = *circ_ptr(runs->b, i++);
		if (run == 1 || run == -1)
		{
			circ_push_back(stacks->b, circ_pop_back(stacks->a));
			merge_output_op(OP_PB);
		}
		else if (run == 2 || run == -2)
		{
			first = circ_pop_back(stacks->a);
			second = circ_pop_back(stacks->a);
			merge_output_op(OP_PB);
			merge_output_op(OP_PB);
			if ((run < 0 && second < first) || (run >= 0 && first < second))
			{
				merge_output_op(OP_SB);
				circ_push_back(stacks->b, second);
				circ_push_back(stacks->b, first);
			}
			else
			{
				circ_push_back(stacks->b, first);
				circ_push_back(stacks->b, second);
			}
		}
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

static void	merge_pass(t_stacks *stacks, t_runs *runs)
{
	int				pass_size;
	int				loc;
	t_merge_state	s;

	runs->current_loc = (runs->current_loc + NUM_LOCS - 1) % NUM_LOCS;
	pass_size = runs->num_runs[(runs->current_loc + NUM_LOCS - 1) % NUM_LOCS];
	loc = 0;
	while (loc < NUM_LOCS)
		runs->num_runs[loc++] -= pass_size;
	runs->num_runs[runs->current_loc] = pass_size;
	runs->total_runs -= 2 * pass_size;
	select_merge_stacks(&s, stacks, runs);
	while (pass_size--)
		merge_run(&s);
}

void	pushswap_merge(t_stacks *stacks, t_runs *runs)
{
	prepare_merge(stacks, runs);
	while (runs->total_runs > 1)
		merge_pass(stacks, runs);
}
