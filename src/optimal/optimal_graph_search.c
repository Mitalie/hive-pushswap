/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_graph_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:17:32 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/04 19:23:25 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimal.h"
#include "optimal_internal.h"
#include "circ.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/*
	Bidirectional breadth-first search: starting with the initial input state
	and the desired sorted state, determine each state's neighbours reachable
	with a single operation. If a neighbour is unvisited, mark it visited,
	record the node and operation it was reached from/by, and add it to queue to
	be analyzed. If a neighbour has already been visited from the opposite
	starting state, merge the paths and terminate the search.
*/
static bool	update_node(t_opt_node *graph,
	t_opt_state_num current, t_opt_state_num found, t_ps_op op)
{
	t_node_state	curr_state;
	t_opt_node		*found_node;

	found_node = &graph[found];
	curr_state = graph[current].state;
	if (found_node->state == NODE_UNVISITED)
	{
		found_node->reached_from_node = current;
		found_node->reached_from_op = op;
		if (curr_state == NODE_REACHED_FROM_END || curr_state == NODE_END)
			found_node->state = NODE_REACHED_FROM_END;
		else
			found_node->state = NODE_REACHED_FROM_START;
		return (true);
	}
	return (false);
}

/*
	Reverse links on the path from start so that they lead towards the end node.
	Reverse operations on the path from end so that they can be executed towards
	the end node.
*/
static void	join_paths(t_opt_node *graph,
	t_opt_state_num from_start, t_opt_state_num from_end, t_ps_op op)
{
	t_opt_state_num	from;
	t_opt_state_num	current;
	t_opt_state_num	next;
	t_ps_op			nextop;

	next = from_start;
	current = from_end;
	while (graph[current].state != NODE_START)
	{
		from = current;
		current = next;
		next = graph[current].reached_from_node;
		graph[current].reached_from_node = from;
	}
	current = from_end;
	while (graph[current].state != NODE_END)
	{
		nextop = op_reverse(graph[current].reached_from_op);
		graph[current].reached_from_op = op;
		op = nextop;
		current = graph[current].reached_from_node;
	}
	graph[current].reached_from_op = op;
}

static bool	finish_search(t_opt_node *graph,
	t_opt_state_num current, t_opt_state_num found, t_ps_op op)
{
	bool			current_end;
	bool			found_end;
	t_node_state	state;

	state = graph[current].state;
	current_end = state == NODE_END || state == NODE_REACHED_FROM_END;
	state = graph[found].state;
	found_end = state == NODE_END || state == NODE_REACHED_FROM_END;
	if (current_end == found_end)
		return (false);
	if (found_end)
		join_paths(graph, current, found, op);
	else
		join_paths(graph, found, current, op_reverse(op));
	return (true);
}

static bool	search_queued_node(t_opt_node *graph, t_circ *queue, int num_items)
{
	t_opt_state_num	current_enc;
	t_opt_state_arr	current;
	t_opt_state_arr	next;
	t_opt_state_num	next_enc;
	t_ps_op			op;

	current_enc = circ_pop_front(queue);
	optimal_state_dec(&current, current_enc, num_items);
	op = 0;
	while (op < NUM_OPS)
	{
		next = current;
		if (optimal_state_op(&next, op))
		{
			next_enc = optimal_state_enc(&next, num_items);
			if (update_node(graph, current_enc, next_enc, op))
				circ_push_back(queue, next_enc);
			else if (finish_search(graph, current_enc, next_enc, op))
				return (true);
		}
		op++;
	}
	return (false);
}

t_ps_status	optimal_graph_search(t_opt_node *graph,
	t_opt_state_num start, t_opt_state_num end, int num_items)
{
	t_circ				*queue;
	int					i;

	queue = circ_alloc(factorial(num_items));
	if (!queue)
		return (PS_ERR_ALLOC_FAILURE);
	i = factorial(num_items + 1);
	while (i)
		graph[--i].state = NODE_UNVISITED;
	graph[start].state = NODE_START;
	graph[end].state = NODE_END;
	circ_push_back(queue, 0);
	circ_push_back(queue, start);
	while (circ_len(queue))
		if (search_queued_node(graph, queue, num_items))
			break ;
	free(queue);
	return (PS_SUCCESS);
}
