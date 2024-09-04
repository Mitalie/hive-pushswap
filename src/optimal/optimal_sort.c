/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:05:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/04 15:58:18 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimal.h"
#include "optimal_internal.h"
#include "circ.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

static int	stacks_to_state(t_stacks *stacks, int num_items)
{
	t_optimal_state	s;
	int				i;

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
	t_state_graph_node	*graph;
	t_ps_status			status;
	int					start;
	int					end;

	end = 0;
	start = stacks_to_state(stacks, num_items);
	if (start == end)
		return (PS_SUCCESS);
	graph = malloc(factorial(num_items + 1) * sizeof(*graph));
	if (!graph)
		return (PS_ERR_ALLOC_FAILURE);
	status = optimal_graph_search(graph, start, end, num_items);
	if (status == PS_SUCCESS)
	{
		while (start != end)
		{
			start = graph[start].reached_from_node;
			printf("%s\n", op_to_string(graph[start].reached_from_op));
		}
	}
	free(graph);
	return (status);
}
