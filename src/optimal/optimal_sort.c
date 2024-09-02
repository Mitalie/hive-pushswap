/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:05:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/02 18:52:30 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimal.h"
#include "optimal_internal.h"
#include "circ.h"
#include <stdlib.h>

static int	fact(int n)
{
	if (n == 0)
		return (1);
	if (n == 1)
		return (1);
	return (n * fact(n - 1));
}

static void	stacks_to_state(t_stacks *stacks, t_optimal_state *s, int num_items)
{
	int	i;

	s->num_a = num_items;
	s->num_b = 0;
	i = 0;
	while (i < num_items)
	{
		s->items[i] = *circ_ptr(stacks->a, num_items - (i + 1));
		i++;
	}
}

/*
	Bidirectional breadth-first search: starting with the initial input state
	and the desired sorted state, determine each state's neighbours reachable
	with a single operation. If a neighbour is unvisited, mark it visited,
	record the node and operation it was reached from/by, and add it to queue to
	be analyzed. If a neighbour has already been visited from the opposite
	starting state, merge the paths and terminate the search.
*/
static bool	update_node(
	t_state_graph_node *graph, int current_enc, int next_enc, t_ps_op op)
{
	if (graph[next_enc].state == SG_UNVISITED)
	{
		graph[next_enc].reached_from_node = current_enc;
		graph[next_enc].reached_from_op = op;
		if (graph[current_enc].state == SG_REACHED_FROM_END)
			graph[next_enc].state = SG_REACHED_FROM_END;
		else
			graph[next_enc].state = SG_REACHED_FROM_START;
		return (true);
	}
	return (false);
}

static const t_ps_op	g_op_reverse[NUM_OPS] = {
[OP_SA] = OP_SA,
[OP_SB] = OP_SA,
[OP_SS] = OP_SS,
[OP_PA] = OP_PB,
[OP_PB] = OP_PA,
[OP_RA] = OP_RRA,
[OP_RB] = OP_RRB,
[OP_RR] = OP_RRR,
[OP_RRA] = OP_RA,
[OP_RRB] = OP_RB,
[OP_RRR] = OP_RR,
};

static bool	finish_search(
	t_state_graph_node *graph, int current_enc, int next_enc, t_ps_op op)
{
	t_state_graph_node	*current;
	t_state_graph_node	*next;
	int					prev_enc;

	current = &graph[current_enc];
	next = &graph[next_enc];
	if (next->state != SG_REACHED_FROM_END
		&& current->state != SG_REACHED_FROM_END)
		return (false);
	if (next->state == SG_REACHED_FROM_END)
	{
		current = &graph[next_enc];
		next = &graph[current_enc];
	}
	while (next->state != SG_START)
	{
		// TODO
	}
	return (true);
}

static void	search_node(t_state_graph_node *graph, t_circ *queue, int num_items)
{
	int				current_enc;
	t_optimal_state	current;
	t_optimal_state	next;
	int				next_enc;
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
				return ;
		}
		op++;
	}
}

t_ps_status	optimal_sort(t_stacks *stacks, int num_items)
{
	t_circ				*queue;
	t_state_graph_node	*graph;
	t_ps_status			status;

	status = PS_SUCCESS;
	graph = malloc(fact(num_items + 1) * sizeof(*graph));
	queue = circ_alloc(fact(num_items));
	if (!graph || !queue)
		status = PS_ERR_ALLOC_FAILURE;
	// TODO
	free(graph);
	free(queue);
	return (status);
}
