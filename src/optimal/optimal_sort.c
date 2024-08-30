/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:05:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/30 18:13:37 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimal.h"
#include "optimal_internal.h"
#include "circ.h"
#include <stdlib.h>

static int	fact(int n)
{
	return (n * fact(n - 1));
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
