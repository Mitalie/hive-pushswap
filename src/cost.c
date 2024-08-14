/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:56:42 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/14 13:01:31 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "runs.h"
#include "cost.h"

static t_run_cost	*init_costs(t_runs *runs)
{
	t_run_cost	*run_costs;
	int			a_runs;
	int			i;

	a_runs = runs->num_runs[A1] + runs->num_runs[A2];
	run_costs = malloc(runs->total_runs * sizeof(*run_costs));
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
		i++;
	}
	return (run_costs);
}

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

static void	swap(t_run_cost **a, t_run_cost **b)
{
	t_run_cost	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static t_run_cost	*sort_costs(t_run_cost *costs, size_t n)
{
	size_t		run_len;
	size_t		start;
	t_run_cost	*dest;

	dest = malloc(n * sizeof(*dest));
	if (dest)
	{
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
			swap(&costs, &dest);
			run_len *= 2;
		}
	}
	free(dest);
	return (costs);
}

bool	select_cheapest(t_runs *runs, int num_items)
{
	t_run_cost	*costs;
	int			i;
	int			run;

	costs = init_costs(runs);
	if (!costs)
		return (false);
	costs = sort_costs(costs, runs->total_runs);
	i = 0;
	while (i < runs->total_runs)
	{
		run = 1;
		if (i >= num_items)
			run = 0;
		else if (*costs[i].run < 0)
			run = -1;
		*costs[i].run = run;
		i++;
	}
	free(costs);
	return (true);
}
