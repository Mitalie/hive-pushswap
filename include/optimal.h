/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:02:28 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/20 17:31:53 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMAL_H
# define OPTIMAL_H

# include "status.h"

typedef struct s_stacks	t_stacks;

/*
	Solve the push_swap assignment for a small number of items using an optimal
	graph-based algorithm.

	Possible states of the push_swap stacks are represented as nodes on a graph,
	and a graph search algorithm is used to find the shortest path of moves from
	the initial input state to the desired sorted state.
*/
t_ps_status	pushswap_optimal(t_stacks *stacks, int num_items, int output_fd);

/*
	With 10 items, there are 11! = 39'916'800 states, requiring ~460 MiB for the
	state graph. This can be done on any reasonable computer.

	With 11 items, there are 12! = 479'001'600 states, requiring ~5.4 GiB. This
	is doable on some computers, but not on the school workstations.

	With 12 items, there are 13! = 6'227'020'800 states and the state number no
	longer fits in a 32-bit int. With 64-bit state numbers the graph grows to
	almost 93 GiB, and the computation time likely becomes unreasonably long
	even if enough memory is available.
*/
# define OPT_MAX_ITEMS 10

#endif
