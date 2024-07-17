/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:13:36 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/17 19:33:59 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "util/state.h"
#include "util/circ.h"
#include "util/const.h"

typedef struct s_node
{
	int		nops;
	t_sop	best_op;
	int		best_op_dest;
}	t_node;

t_node	g_graph[220 * 362880];

void	search_node(int nops, t_circular *queue)
{
	t_state	s;
	t_state	ns;
	int		nv;
	int		i;
	int		v;

	v = circ_shift(queue);
	s = decode(v);
	i = 0;
	while (i < NUM_SOP)
	{
		ns = s;
		if (sop(&ns, i))
		{
			nv = encode(&ns);
			if (!g_graph[nv].nops)
			{
				g_graph[nv].nops = nops + 1;
				g_graph[nv].best_op = i;
				g_graph[nv].best_op_dest = v;
				circ_push(queue, nv);
			}
		}
		i++;
	}
}

static const char	*g_rev_op_names[NUM_SOP] = {
	"ss", "sa", "sb",
	"rrr", "rra", "rrb",
	"rr", "ra", "rb",
	"pb", "pa"
};

void	printpath(int v)
{
	t_state	s;

	printf("    %d : ", v);
	s = decode(v);
	printstate(&s);
	printf("    ");
	while (g_graph[v].nops > 1)
	{
		printf(" %s", g_rev_op_names[g_graph[v].best_op]);
		v = g_graph[v].best_op_dest;
	}
	printf("\n");
}

void	scanset(int setidx, const char *locname)
{
	int	max_in_set;
	int	i;
	size_t	total_in_set;

	max_in_set = 0;
	i = setidx * g_fact[N];
	total_in_set = 0;
	while (i < (setidx + 1) * g_fact[N])
	{
		if (max_in_set < g_graph[i].nops)
			max_in_set = g_graph[i].nops;
		//printpath(i);
		total_in_set += g_graph[i].nops;
		i++;
	}
	printf("sort %d from %s: max %d, avg %f \n", N, locname, max_in_set - 1, (double)total_in_set / g_fact[N] - 1);
}

int	main(void)
{
	t_circular	queue;
	size_t		nodes_on_level;
	size_t		total_missing;
	size_t		nops;

	circ_init(&queue, g_fact[N] * (g_te[N] + g_t[N] + N + 1));
	circ_push(&queue, 0);
	nops = 1;
	total_missing = queue.size - 1;
	g_graph[0].nops = 1;
	while (queue.count)
	{
		nodes_on_level = queue.count;
		while (nodes_on_level--)
			search_node(nops, &queue);
		total_missing -= queue.count;
		printf("found %8zu reachable with %2zu moves, still looking for %8zu\n",
			queue.count, nops, total_missing);
		nops++;
	}
	circ_deinit(&queue);
	scanset(0, "top of A");
	scanset(g_te[N], "bottom of A");
	scanset(g_te[N] + g_t[N], "top of B");
	scanset(g_te[N] + g_t[N] + N, "bottom of B");
}
