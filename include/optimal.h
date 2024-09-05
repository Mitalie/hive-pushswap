/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:02:28 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/05 16:04:33 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMAL_H
# define OPTIMAL_H

# include "status.h"
# include "stacks.h"

/*
	With 10 items, there are 11! = 39'916'800 states, requiring ~460 MiB for the
	state graph. This is doable.

	With 11 items, there are 12! = 479'001'600 states, requiring ~5.4 GiB. This
	is doable on some computers, but not on the school workstations.

	With 12 items, there are 13! = 6'227'020'800 states, the state number no
	longer fits in a 32-bit int, and with 64-bit state numbers the graph grows
	to almost 93 GiB.
*/
# define OPT_MAX_ITEMS 11

/*
	For a small number of items, it is possible to construct a graph of all the
	possible states and the operations that move between them, and use a graph
	search algorithm to find the shortest path from starting state to the
	desired final state.
*/
t_ps_status	optimal_sort(t_stacks *stacks, int num_items);

#endif
