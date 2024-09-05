/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:05:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/05 16:11:49 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimal.h"
#include "optimal_internal.h"
#include "circ.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

static t_opt_state_num	stacks_to_state(t_stacks *stacks, int num_items)
{
	t_opt_state_arr	s;
	t_opt_state_num	i;

	s.num_a = num_items;
	s.num_b = 0;
	i = 0;
	while (i < num_items)
	{
		s.items[i] = *circ_ptr(stacks->a, num_items - (i + 1));
		i++;
	}
	return (optimal_state_enc(&s, num_items));
}

t_ps_status	optimal_sort(t_stacks *stacks, int num_items)
{
	t_opt_graph		graph;
	t_ps_status		status;
	t_opt_state_num	start;
	t_opt_state_num	end;

	end = OPT_SORTED_STATE_NUM;
	start = stacks_to_state(stacks, num_items);
	if (start == end)
		return (PS_SUCCESS);
	graph.reached_from_node = malloc(factorial(num_items + 1) * sizeof(*graph.reached_from_node));
	graph.states = malloc(factorial(num_items + 1) * sizeof(*graph.states));
	status = PS_SUCCESS;
	if (!graph.reached_from_node || ! graph.states)
		status = PS_ERR_ALLOC_FAILURE;
	if (status == PS_SUCCESS)
		status = optimal_graph_search(&graph, start, end, num_items);
	if (status == PS_SUCCESS)
	{
		while (start != end)
		{
			start = graph.reached_from_node[start];
			printf("%s\n", op_to_string(graph.states[start].reached_from_op));
		}
	}
	free(graph.reached_from_node);
	free(graph.states);
	return (status);
}
