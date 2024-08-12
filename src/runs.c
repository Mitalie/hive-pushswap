/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:02:21 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/12 17:45:16 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runs.h"
#include <stdlib.h>

static void	reset_runs(t_runs *runs)
{
	int	i;

	i = 0;
	while (i < NUM_LOCS)
		runs->num_runs[i++] = 0;
	runs->current_loc = A1;
	runs->num_runs[A1] = 1;
	runs->total_runs = 1;
}

static void	count_pass(t_runs *runs)
{
	int		current_pass_size;
	t_loc	loc;

	current_pass_size = runs->num_runs[runs->current_loc];
	loc = 0;
	while (loc < NUM_LOCS)
		runs->num_runs[loc++] += current_pass_size;
	runs->num_runs[runs->current_loc] = 0;
	runs->total_runs += 2 * current_pass_size;
	runs->current_loc = (runs->current_loc + 1) % NUM_LOCS;
}

static void	split_pass(t_runs *runs)
{
	int		i;
	int		dir;
	int		run;
	t_circ	*curr;
	t_circ	*other;

	i = runs->num_runs[runs->current_loc];
	curr = runs->a;
	if (runs->current_loc >= B1)
		curr = runs->b;
	other = runs->b;
	if (runs->current_loc >= B1)
		other = runs->a;
	while (i--)
	{
		run = circ_pop_back(curr);
		dir = 1;
		if (run < 0)
			dir = -1;
		run += dir;
		circ_push_front(curr, run);
		circ_push_back(other, -run);
		run += dir;
		circ_push_front(other, run);
	}
}

bool	init_runs(t_runs *runs, int num_items)
{
	reset_runs(runs);
	while (runs->total_runs < num_items)
		count_pass(runs);
	runs->a = circ_alloc(runs->num_runs[A1] + runs->num_runs[A2]);
	if (!runs->a)
		return (false);
	runs->b = circ_alloc(runs->num_runs[B1] + runs->num_runs[B2]);
	if (!runs->b)
		return (false);
	reset_runs(runs);
	circ_push_back(runs->a, 0);
	while (runs->total_runs < num_items)
	{
		split_pass(runs);
		count_pass(runs);
	}
	return (true);
}
