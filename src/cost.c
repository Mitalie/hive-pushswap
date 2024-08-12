/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:56:42 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/12 17:55:40 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "runs.h"
#include "cost.h"

static int	get_run_cost(t_circ *circ, size_t idx)
{
	int	run;

	run = circ_get(circ, idx);
	if (run < 0)
		return (-run);
	return (run);
}

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
	while (i < a_runs)
	{
		run_costs[i].stack = 0;
		run_costs[i].pos = i;
		run_costs[i].cost = get_run_cost(runs->a, i);
		i++;
	}
	while (i < runs->total_runs)
	{
		run_costs[i].stack = 1;
		run_costs[i].pos = i - a_runs;
		run_costs[i].cost = get_run_cost(runs->b, i - a_runs);
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
	t_circ		*stack;
	int			i;
	int			run;

	costs = init_costs(runs);
	if (!costs)
		return (false);
	costs = sort_costs(costs, runs->total_runs);
	i = 0;
	while (i < runs->total_runs)
	{
		stack = runs->a;
		if (costs[i].stack != 0)
			stack = runs->b;
		run = 1;
		if (i >= num_items)
			run = 0;
		else if (circ_get(stack, costs[i].pos) < 0)
			run = -1;
		circ_set(stack, costs[i].pos, run);
		i++;
	}
	free(costs);
	return (true);
}
