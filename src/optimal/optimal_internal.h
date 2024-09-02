/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:04:59 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/02 16:48:17 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMAL_INTERNAL_H
# define OPTIMAL_INTERNAL_H

# include "ops.h"
# include <stdbool.h>

# define OPTIMAL_MAX_ITEMS 9

typedef enum e_node_state
{
	SG_UNVISITED,
	SG_END,
	SG_REACHED_FROM_START,
	SG_REACHED_FROM_END,
}	t_node_state;

/*
	We can fully represent the state of push_swap stacks with `n` items by
	encoding the order of items on the stacks as a permutation number `N` (e.g.
	Lehmer code) with `0 <= N < n!`, and the split between stacks A and B by
	number of items on stack B. These can be combined to a single number
	`S = N * (n + 1) + B` with `0 <= S < (n + 1)!`. For small numbers of items,
	we can have an array of all states, and store within each the next state
	number on the shortest path to a particular state.
*/
typedef struct s_state_graph_node
{
	t_node_state	state;
	t_ps_op			reached_from_op;
	int				reached_from_node;
}	t_state_graph_node;

/*
	Compact fixed size representation of push_swap stacks, enabling push_swap
	operations on it while being easy to convert to and from state numbers.
	- items[0] is bottom of B
	- items[num_b - 1] is top of B
	- items[num_b] is top of A
	- items[num_b + num_a - 1] is bottom of A

	With this layout, pa/pb require no moving of elements, and the desired
	sorted state has items in order [1, 2, ..., n-1, n] regardless of n. By
	using Lehmer code, this permutation encodes to value 0.
*/
typedef struct s_optimal_state
{
	int	num_a;
	int	num_b;
	int	items[OPTIMAL_MAX_ITEMS];
}	t_optimal_state;

int		optimal_state_enc(t_optimal_state *s, int num_items);
void	optimal_state_dec(t_optimal_state *s, int state_num, int num_items);
bool	optimal_state_op(t_optimal_state *s, t_ps_op op);

#endif
