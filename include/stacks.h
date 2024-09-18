/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:14:46 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/18 17:39:07 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKS_H
# define STACKS_H

# include "circ.h"
# include "status.h"

/*
	A struct to store the A and B stacks described in the push_swap assignment.
	The front of each `t_circ` will be considered the bottom of each stack.
*/
typedef struct s_stacks
{
	t_circ	*a;
	t_circ	*b;
}	t_stacks;

/*
	Allocate and initialize the stacks and process input from an argv-style
	string array. Input items will be placed on stack A, first item on top and
	last item on bottom. Each string must be a valid int with no extra garbage
	besides leading or trailing whitespace. The allocated memory must be
	released with `release_stacks`.
*/
t_ps_status	input_to_stacks(t_stacks *s, size_t num_items, char **item_strs);

void		release_stacks(t_stacks *s);

#endif
