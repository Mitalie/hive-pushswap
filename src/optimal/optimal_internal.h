/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:04:59 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/05 16:14:14 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMAL_INTERNAL_H
# define OPTIMAL_INTERNAL_H

# include "optimal.h"
# include "ops.h"
# include <stdbool.h>

/*
	Very compact representation of push_swap stacks, encoding the state in a
	single integer but limited to a small number of items.

	The order (permutation) of items is converted into Lehmer code, and, using
	factorial number system, into an integer `N` with `0 <= N < n!`. We combine
	it with number of items on stack B into a single state number
	`S = N * (n + 1) + B` with `0 <= S < (n + 1)!`.
*/
typedef int	t_opt_state_num;

/*
	Compact array representation of push_swap stacks, enabling push_swap
	operations on it while being easy to convert to and from state numbers.

	- `items[0]` is bottom of B
	- `items[num_b - 1]` is top of B
	- `items[num_b]` is top of A
	- `items[num_b + num_a - 1]` is bottom of A

	With this layout, pa/pb require no moving of elements, and the desired
	sorted state has items in order `1, 2, ..., n-1, n` regardless of number of
	items. By using Lehmer code, this permutation encodes to value 0.
*/
typedef struct s_opt_state_arr
{
	int	num_a;
	int	num_b;
	int	items[OPT_MAX_ITEMS];
}	t_opt_state_arr;

# define OPT_SORTED_STATE_NUM 0

typedef enum e_node_state
{
	NODE_UNVISITED,
	NODE_START,
	NODE_END,
	NODE_REACHED_FROM_START,
	NODE_REACHED_FROM_END,
}	t_node_state;

typedef struct s_opt_node
{
	unsigned char	state : 3;
	char			reached_from_op : 5;
}	t_opt_node;
typedef struct s_opt_graph
{
	t_opt_node		*states;
	t_opt_state_num	*reached_from_node;
}	t_opt_graph;

t_opt_state_num	optimal_state_enc(t_opt_state_arr *s, int num_items);
void			optimal_state_dec(t_opt_state_arr *s,
					t_opt_state_num state_num, int num_items);
bool			optimal_state_op(t_opt_state_arr *s, t_ps_op op);
t_ps_status		optimal_graph_search(t_opt_graph *graph,
					t_opt_state_num start, t_opt_state_num end, int num_items);

#endif
