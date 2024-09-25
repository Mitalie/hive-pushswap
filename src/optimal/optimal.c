/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:05:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/25 13:36:29 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimal.h"

#include "circ.h"
#include "op.h"
#include "optimal_internal.h"
#include "stacks.h"
#include "util.h"
#include <stdlib.h>

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

t_ps_status	pushswap_optimal(t_stacks *stacks, int num_items, int output_fd)
{
	t_opt_node		*graph;
	t_ps_status		status;
	t_opt_state_num	start;
	t_opt_state_num	end;

	end = OPT_SORTED_STATE_NUM;
	start = stacks_to_state(stacks, num_items);
	if (start == end)
		return (PS_SUCCESS);
	graph = malloc(util_factorial(num_items + 1) * sizeof(*graph));
	if (!graph)
		return (PS_ERR_ALLOC_FAILURE);
	status = optimal_graph_search(graph, start, end, num_items);
	while (status == PS_SUCCESS && start != end)
	{
		status = op_write(output_fd, graph[start].op);
		start = graph[start].reached_from;
	}
	free(graph);
	return (status);
}
