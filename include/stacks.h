/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:14:46 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/20 17:32:53 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKS_H
# define STACKS_H

# include "status.h"
# include <stddef.h>

typedef struct s_circ	t_circ;

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
	released with `stacks_release`.
*/
t_ps_status	stacks_from_input(t_stacks *s, size_t num_items, char **item_strs);

void		stacks_release(t_stacks *s);

#endif
