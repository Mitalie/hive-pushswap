/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:14:46 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/19 16:47:09 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKS_H
# define STACKS_H

# include "circ.h"
# include "status.h"

typedef struct s_stacks
{
	t_circ	*a;
	t_circ	*b;
}	t_stacks;

t_ps_status	input_to_stacks(t_stacks *s, size_t num_items, char **item_strs);

#endif
