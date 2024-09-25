/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs_populate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:13:50 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/25 13:49:22 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runs_internal.h"

#include "circ.h"

static void	reset_runs(t_runs *runs)
{
	int	loc;

	loc = 0;
	while (loc < NUM_LOCS)
		runs->num_runs[loc++] = 0;
	runs->current_loc = A1;
	runs->num_runs[A1] = 1;
	runs->total_runs = 1;
}

/*
	Calculate and allocate required sizes for the run buffers for given number
	of passes, then reset the other fields for iteration by merge_runs_populate.
*/
static t_ps_status	runs_init(t_runs *runs, size_t passes)
{
	int		pass_size;
	t_loc	loc;

	reset_runs(runs);
	while (passes--)
	{
		pass_size = runs->num_runs[runs->current_loc];
		loc = 0;
		while (loc < NUM_LOCS)
			runs->num_runs[loc++] += pass_size;
		runs->num_runs[runs->current_loc] = 0;
		runs->total_runs += 2 * pass_size;
		runs->current_loc = (runs->current_loc + 1) % NUM_LOCS;
	}
	runs->a = circ_alloc(runs->num_runs[A1] + runs->num_runs[A2]);
	runs->b = circ_alloc(runs->num_runs[B1] + runs->num_runs[B2]);
	reset_runs(runs);
	if (!runs->a || !runs->b)
		return (PS_ERR_ALLOC_FAILURE);
	return (PS_SUCCESS);
}

/*
	Take one run entry where absolute value represents cost of merging from this
	run into the final sorted output, and sign represents the run direction.
	Split this run into the source runs that will be merged to create it,
	adjusting cost and direction accordingly.
*/
static void	split_single_run(t_circ *curr, t_circ *other)
{
	int	run;
	int	dir;

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

/*
	Split every run entry in the current location, adjust the run counts, and
	move on to next location.
*/
static void	split_pass(t_runs *runs)
{
	int		pass_size;
	int		i;
	t_loc	loc;

	pass_size = runs->num_runs[runs->current_loc];
	i = 0;
	if (runs->current_loc >= B1)
		while (i++ < pass_size)
			split_single_run(runs->b, runs->a);
	else
		while (i++ < pass_size)
			split_single_run(runs->a, runs->b);
	loc = 0;
	while (loc < NUM_LOCS)
		runs->num_runs[loc++] += pass_size;
	runs->num_runs[runs->current_loc] = 0;
	runs->total_runs += 2 * pass_size;
	runs->current_loc = (runs->current_loc + 1) % NUM_LOCS;
}

/*
	Split the final sorted output run into the initial runs from which it will
	be merged in the given number of passes, tracking the cost and direction of
	each run in the process and allowing a callback to investigate the state
	after each pass.
*/
t_ps_status	merge_runs_populate(
	t_runs *runs, size_t passes, t_pass_cb *callback)
{
	size_t		pass;
	t_ps_status	status;

	status = runs_init(runs, passes);
	if (status != PS_SUCCESS)
		return (status);
	circ_push_back(runs->a, 0);
	pass = 0;
	while (pass++ < passes)
	{
		split_pass(runs);
		if (callback)
		{
			status = callback->func(runs, pass, callback);
			if (status != PS_SUCCESS)
				return (status);
		}
	}
	return (PS_SUCCESS);
}
