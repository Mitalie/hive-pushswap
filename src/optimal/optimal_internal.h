/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:04:59 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/30 18:03:03 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMAL_INTERNAL_H
# define OPTIMAL_INTERNAL_H

# include "ops.h"

# define OPTIMAL_MAX_ITEMS 9

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
	int		distance;
	t_ps_op	best_op;
	int		best_op_node;
}	t_state_graph_node;

/*
	Compact fixed size representation of push_swap stacks, enabling push_swap
	operations on it while being easy to convert to and from state numbers.
*/
typedef struct s_optimal_state
{
	unsigned char	num_on_b;
	unsigned char	digits[OPTIMAL_MAX_ITEMS];
}	t_optimal_state;

int		optimal_state_enc(t_optimal_state *state);
void	optimal_state_dec(t_optimal_state *state, int state_num);
int		optimal_state_op(int state_num, t_ps_op	op);

#endif
