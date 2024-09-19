/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:31:31 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/19 16:34:00 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_INTERNAL_H
# define MERGE_INTERNAL_H

# include "circ.h"
# include "ops.h"
# include "status.h"

/*
	This module solves the push_swap assignment with polyphase merge sort.

	Merge sort merges two or more sorted runs (sequences) into a longer sorted
	run in O(n) operations. It requires O(log n) passes to go from n runs of
	length 1 to one run of length n, for total complexity O(n log n). Inputs are
	processed sequentially, which makes it suitable for the push_swap stacks
	where access to the middle would require multiple rotation ops.

	The tops and bottoms of the push_swap stacks give us four locations to use
	as either inputs or outputs. Using more inputs reduces the number of merge
	passes required as the sorted run length grows faster, but a typical
	balanced merge sort either requires half the locations as outputs or needs
	to redistribute the runs before next pass. Polyphase merge sort uses only
	one output location at a time and requires no redistribution by operating
	with an uneven distribution of runs. Whenever an input location is emptied
	it becomes the new output. Initial distribution of runs is chosen so that
	only one input location becomes empty at a time, except for the final merge
	that empties all inputs to produce a single sorted run. A single pass (until
	change of output location) doesn't merge all runs, so run lengths become
	unequal and we must keep track of each run's length as we merge runs
	together.

	Outputting to the bottom of a stack requires more ops than the top, so we
	avoid doing so. We swap the roles of top and bottom whenever the bottom
	location is empty and becomes the next output location - the previous "top"
	location is also accessible via bottom as there is nothing under it, and we
	can start outputting on the previous "bottom" location via top instead.

	Runs written on top and read from bottom retain their direction, but to use
	three inputs some items must be read from the top of a stack and come out in
	LIFO order. These runs must be written in opposite direction relative to the
	merge that consumes them, so we must calculate the direction of each run to
	be created. We calculate backwards from the final merge, splitting each run
	to its merged input runs, and keep track of the direction of each run until
	we have enough runs to consider each input item a run of length 1.

	Merging from the bottom of the stack opposite to output requires two ops
	while merging from bottom of output stack or top of other stack requires
	only one. While splitting the runs we keep track of the total merge cost of
	each run, and assign the items to the cheapest ones. We run a few additional
	split passes beyond the minimum and select the cheapest total cost, as for
	many input sizes avoiding the most expensive runs saves more ops than the
	extra merge passes cost.

	The merge sort produces a fixed number of ops to sort a given number of
	items, regardless of the initial order, as each merge needs to move all
	items from inputs to output, and only the order of those moves change. We
	pass the resulting ops through a filter which tries to omit or combine them
	when it won't change the result. This reduces the number of ops but adds
	some variance.
*/

/*
	Tops and bottoms of each stack gives us a total of four locations to use for
	sorting. We don't explicitly label the locations as top and bottom as we
	swap their roles to avoid outputting to bottom for its higher op cost.
*/
typedef enum e_loc
{
	A1,
	A2,
	B1,
	B2,
	NUM_LOCS,
}	t_loc;

/*
	We keep track of run directions and costs (while splitting) or directions
	and lengths (while merging) in a structure mirroring t_stacks, but during
	both processes we also need to keep track of the current location and the
	number of runs in each location.
*/
typedef struct s_runs
{
	t_loc	current_loc;
	int		num_runs[NUM_LOCS];
	int		total_runs;
	t_circ	*a;
	t_circ	*b;
}	t_runs;

/*
	Generate the starting runs for the polyphase merge sort, calculating their
	directions and costs and selecting the cheapest ones to be used for the
	items.
*/
t_ps_status	calculate_runs(t_runs *runs, int num_items);

/*
	The output stack is considered "current" and output always happens on top.
	The other three locations are the possible inputs, from which the next item
	(largest or smallest) needs to be selected.
*/
typedef enum e_merge_source
{
	CURR_BOT,
	OTHER_TOP,
	OTHER_BOT,
	NUM_SOURCES
}	t_merge_source;

/*
	Variables that live for the entire merge sort process and are needed in the
	inner functions.
*/
typedef struct s_merge_state
{
	size_t		output_queue_size;
	t_circ		*output_queue;
	int			output_fd;
	t_stacks	*stacks;
}	t_merge_state;

/*
	Variables that reset for each pass during the merge.

	These essentially cache the choice of current destination stack (A or B) to
	eliminate repeated checks and code duplication in inner functions.
*/
typedef struct s_merge_pass_state
{
	t_circ					*runs_curr;
	t_circ					*runs_other;
	t_circ					*data_curr;
	t_circ					*data_other;
	const t_ps_op *const	*pushswap_ops;
}	t_merge_pass_state;

/*
	Variables that reset for each run during a pass and are needed in the inner
	functions.
*/
typedef struct s_merge_run_state
{
	int	run_items[NUM_SOURCES];
	int	run_dir;
}	t_merge_run_state;

t_ps_status	merge_run(t_merge_state *merge, t_merge_pass_state *pass);

t_ps_status	merge_op_queue_add(t_merge_state *merge, t_ps_op op);
t_ps_status	merge_op_queue_flush(t_merge_state *merge);

#endif
