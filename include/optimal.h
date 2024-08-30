/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:02:28 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/30 17:59:05 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMAL_H
# define OPTIMAL_H

# include "status.h"
# include "stacks.h"

/*
	For a small number of items, it is possible to construct a graph of all the
	possible states and the operations that move between them, and use a graph
	search algorithm to find the shortest path from starting state to the
	desired final state.
*/
t_ps_status	optimal_sort(t_stacks *stacks, int num_items);

#endif
