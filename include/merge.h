/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:41:35 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/19 16:34:02 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_H
# define MERGE_H

# include "status.h"
# include "stacks.h"

/*
	Solve the push_swap assignment large number of items using a merge sort
	algorithm.

	Merge sort merges two or more sorted runs (sequences) into a longer sorted
	run in O(n) operations. It requires O(log n) passes to go from n runs of
	length 1 to one run of length n, for total complexity O(n log n). Inputs are
	processed sequentially, which makes it suitable for the push_swap stacks and
	operations where random access would require expensive rotations.
*/
t_ps_status	pushswap_merge(t_stacks *stacks, int num_items, int output_fd);

#endif
