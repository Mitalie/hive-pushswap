/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:44:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/19 15:13:12 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circ.h"
#include "merge.h"
#include "merge_internal.h"
#include <stdio.h>

static void	prepare_merge(t_stacks *stacks, t_runs *runs)
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
		circ_push_back(stacks->b, circ_pop_back(stacks->a));
		printf("pb\n");
	}
}

static const char	*g_ops_to_a[NUM_SOURCES] = {"rra", "pa", "rrb\npa"};
static const char	*g_ops_to_b[NUM_SOURCES] = {"rrb", "pb", "rra\npb"};

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
