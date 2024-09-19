/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:21:00 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/19 17:35:13 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"
#include "util.h"
#include <stdlib.h>

/*
	The assignment specifies that the first argument should be at the top of the
	stack. We consider the front of the circular buffer to be the bottom of the
	stack, so we put each argument under the previous ones with circ_push_front.
*/

t_ps_status	stacks_from_input(t_stacks *s, size_t num_items, char **item_strs)
{
	int		value;
	size_t	item_idx;
	size_t	scan_idx;

	s->a = circ_alloc(num_items);
	s->b = circ_alloc(num_items);
	if (!s->a || !s->b)
		return (PS_ERR_ALLOC_FAILURE);
	item_idx = 0;
	while (item_idx < num_items)
	{
		if (!util_parse_int(item_strs[item_idx], &value))
			return (PS_ERR_INPUT_ITEM_INVALID);
		scan_idx = 0;
		while (scan_idx < item_idx)
			if (value == *circ_ptr(s->a, scan_idx++))
				return (PS_ERR_INPUT_ITEM_DUPLICATE);
		circ_push_front(s->a, value);
		item_idx++;
	}
	return (PS_SUCCESS);
}

void	stacks_release(t_stacks *s)
{
	free(s->a);
	free(s->b);
}
