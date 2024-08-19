/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:14:46 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/19 14:11:08 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKS_H
# define STACKS_H

# include <stdbool.h>
# include "circ.h"

typedef struct s_stacks
{
	t_circ	*a;
	t_circ	*b;
}	t_stacks;

bool	input_to_stacks(t_stacks *s, size_t num_items, char **item_strs);

#endif
