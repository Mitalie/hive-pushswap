/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_graph_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:17:32 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/06 18:39:45 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimal_internal.h"
#include <stdlib.h>
#include "circ.h"
#include "util.h"

static bool	search_queued_node(t_opt_node *graph, t_circ *queue, int num_items);
static bool	visit_node(t_opt_node *graph, t_opt_state_num current,
				t_opt_state_num found, t_ps_op op);
static bool	finish_search(t_opt_node *graph, t_opt_state_num current,
				t_opt_state_num found, t_ps_op op);
static void	join_paths(t_opt_node *graph, t_opt_state_num from_start,
				t_opt_state_num from_end, t_ps_op op);

/*
	Bidirectional breadth-first search: starting with the given start and end
	states, determine each state's neighbours reachable with a single operation.
	If a neighbour is unvisited, mark it visited, record the node and operation
	it was reached from/by, and add it to queue to be analyzed. If a neighbour
	has already been visited from the opposite starting state, merge the paths
	so that it can be traversed from start to end, and terminate the search.

	Queue space equal to the number of states is much more than necessary, but
	the actual space required is difficult to determine beforehand. Most of the
	queue space will never be touched,	so the operating system likely reserves
	no physical memory pages for it.
*/
t_ps_status	optimal_graph_search(t_opt_node *graph,
	t_opt_state_num start, t_opt_state_num end, int num_items)
{
	t_circ				*queue;
	int					i;

	i = factorial(num_items + 1);
	queue = circ_alloc(i);
	if (!queue)
		return (PS_ERR_ALLOC_FAILURE);
	while (i)
		graph[--i].type = NODE_UNVISITED;
	graph[start].type = NODE_START;
	graph[end].type = NODE_END;
	circ_push_back(queue, 0);
	circ_push_back(queue, start);
	while (circ_len(queue))
		if (search_queued_node(graph, queue, num_items))
			break ;
	free(queue);
	return (PS_SUCCESS);
}

/*
	Process one node from the queue, return true if a path was found.
*/
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
			if (visit_node(graph, current_enc, next_enc, op))
				circ_push_back(queue, next_enc);
			else if (finish_search(graph, current_enc, next_enc, op))
				return (true);
		}
		op++;
	}
	return (false);
}

/*
	Try to visit an unvisited node, return false if the found node was already
	visited.
*/
static bool	visit_node(t_opt_node *graph,
	t_opt_state_num current, t_opt_state_num found, t_ps_op op)
{
	t_opt_node_type	curr_type;
	t_opt_node		*found_node;

	found_node = &graph[found];
	curr_type = graph[current].type;
	if (found_node->type == NODE_UNVISITED)
	{
		found_node->reached_from = current;
		found_node->op = op;
		if (curr_type == NODE_REACHED_FROM_END || curr_type == NODE_END)
			found_node->type = NODE_REACHED_FROM_END;
		else
			found_node->type = NODE_REACHED_FROM_START;
		return (true);
	}
	return (false);
}

/*
	Try to connect the from-start and from-end search fronts, return false if
	the found node and current node are part of the same front. Must not be
	called with unvisited nodes.
*/
static bool	finish_search(t_opt_node *graph,
	t_opt_state_num current, t_opt_state_num found, t_ps_op op)
{
	bool			current_end;
	bool			found_end;
	t_opt_node_type	type;

	type = graph[current].type;
	current_end = (type == NODE_END || type == NODE_REACHED_FROM_END);
	type = graph[found].type;
	found_end = (type == NODE_END || type == NODE_REACHED_FROM_END);
	if (current_end == found_end)
		return (false);
	if (found_end)
		join_paths(graph, current, found, op);
	else
		join_paths(graph, found, current, op_reverse(op));
	return (true);
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
	while (graph[current].type != NODE_START)
	{
		from = current;
		current = next;
		next = graph[current].reached_from;
		graph[current].reached_from = from;
	}
	current = from_end;
	while (graph[current].type != NODE_END)
	{
		nextop = op_reverse(graph[current].op);
		graph[current].op = op;
		op = nextop;
		current = graph[current].reached_from;
	}
	graph[current].op = op;
}
