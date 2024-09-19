/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:02:21 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/19 17:41:46 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runs_internal.h"
#include <stdlib.h>

/*
	The number of runs A used by N passes of polyphase mergesort is
	A(N)=A(N-1)+A(N-2)+A(N-3), with A(0)=1, A(-1)=1, A(-2)=1. As a baseline
	estimate, we need at least one run per item to start with runs of length 1.
	Excess runs are simply considered to be of length zero.
*/
static size_t	calc_num_passes(size_t num_items)
{
	size_t	sum;
	size_t	prev1;
	size_t	prev2;
	size_t	newsum;
	size_t	passes;

	sum = 1;
	prev1 = 1;
	prev2 = 1;
	passes = 0;
	while (sum < num_items)
	{
		newsum = sum + prev1 + prev2;
		prev2 = prev1;
		prev1 = sum;
		sum = newsum;
		passes++;
	}
	return (passes);
}

/*
	Merging from the bottom of opposite stack requires two moves instead of one.
	Additional split passes often reduce total sorting cost by creating larger
	number of cheap runs and eliminating use of more expensive ones. Calculate
	total cost for sorting N items after each split pass to determine which
	number of passes is cheapest.
*/
static t_ps_status	check_cost_callback(
	t_runs *runs, size_t pass, t_pass_cb *cb)
{
	t_ps_status	status;
	size_t		cost;

	if (runs->total_runs >= cb->num_items)
	{
		status = merge_runs_get_cost(runs, cb->num_items, &cost);
		if (status != PS_SUCCESS)
			return (status);
		if (cost < cb->best_cost)
		{
			cb->best_pass = pass;
			cb->best_cost = cost;
		}
	}
	return (PS_SUCCESS);
}

/*
	Each pass increases memory usage and calculation time. 4th extra pass first
	becomes optimal at 21332 items, so 3 extra passes is sufficient for now.
*/
#define EXTRA_PASSES 3

t_ps_status	merge_runs_generate(t_runs *runs, int num_items)
{
	size_t		passes;
	t_ps_status	status;
	t_pass_cb	cb;

	passes = calc_num_passes(num_items) + EXTRA_PASSES;
	cb.func = check_cost_callback;
	cb.best_pass = 0;
	cb.best_cost = -1;
	cb.num_items = num_items;
	status = merge_runs_populate(runs, passes, &cb);
	if (status != PS_SUCCESS)
		return (status);
	merge_runs_release(runs);
	status = merge_runs_populate(runs, cb.best_pass, 0);
	if (status != PS_SUCCESS)
		return (status);
	return (merge_runs_select_cheapest(runs, num_items));
}

void	merge_runs_release(t_runs *runs)
{
	free(runs->a);
	free(runs->b);
}
