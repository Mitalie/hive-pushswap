/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:56:42 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/26 14:58:34 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "runs.h"
#include "runs_internal.h"

/*
	Allocate space for enough cost entries and initialize them based on the run
	candidate buffers. Double space is allocated for merge sorting.
*/
static t_run_cost	*init_costs(t_runs *runs)
{
	t_run_cost	*run_costs;
	int			a_runs;
	int			i;

	a_runs = runs->num_runs[A1] + runs->num_runs[A2];
	run_costs = malloc(runs->total_runs * sizeof(*run_costs) * 2);
	if (!run_costs)
		return (0);
	i = 0;
	while (i < runs->total_runs)
	{
		if (i < a_runs)
			run_costs[i].run = circ_ptr(runs->a, i);
		else
			run_costs[i].run = circ_ptr(runs->b, i - a_runs);
		run_costs[i].cost = *run_costs[i].run;
		if (run_costs[i].cost < 0)
			run_costs[i].cost = -run_costs[i].cost;
		if (i >= a_runs)
			run_costs[i].cost++;
		i++;
	}
	return (run_costs);
}

/*
	Merge two consecutive ascending sequences of cost entries into one.
*/
static void	merge_run(t_run_cost *dst, t_run_cost *src, size_t n_a, size_t n_b)
{
	size_t	i_a;
	size_t	i_b;

	i_a = 0;
	i_b = 0;
	while (i_a < n_a || i_b < n_b)
	{
		if (i_a < n_a && (i_b >= n_b || src[i_a].cost < src[n_a + i_b].cost))
		{
			dst[i_a + i_b] = src[i_a];
			i_a++;
		}
		else
		{
			dst[i_a + i_b] = src[n_a + i_b];
			i_b++;
		}
	}
}

/*
	Sort an array of cost entries, lowest cost first, using merge sort and
	utilizing the extra space allocated by init_costs.
*/
static t_run_cost	*sort_costs(t_run_cost *costs, size_t n)
{
	size_t		run_len;
	size_t		start;
	t_run_cost	*dest;
	t_run_cost	*tmp;

	dest = costs + n;
	run_len = 1;
	while (run_len < n)
	{
		start = 0;
		while (start + run_len * 2 <= n)
		{
			merge_run(dest + start, costs + start, run_len, run_len);
			start += run_len * 2;
		}
		if (start + run_len <= n)
			merge_run(dest + start, costs + start,
				run_len, n - start - run_len);
		tmp = costs;
		costs = dest;
		dest = tmp;
		run_len *= 2;
	}
	return (costs);
}

/*
	Select cheapest runs from the run candidate buffers and replace directions
	and costs with directions and run lengths.
*/
t_ps_status	runs_select_cheapest(t_runs *runs, int num_items)
{
	t_run_cost	*costs;
	t_run_cost	*sorted;
	int			i;
	int			run;

	costs = init_costs(runs);
	if (!costs)
		return (PS_ERR_ALLOC_FAILURE);
	sorted = sort_costs(costs, runs->total_runs);
	i = 0;
	while (i < runs->total_runs)
	{
		run = 1;
		if (i >= num_items)
			run = 0;
		else if (*sorted[i].run < 0)
			run = -1;
		*sorted[i].run = run;
		i++;
	}
	free(costs);
	return (PS_SUCCESS);
}
