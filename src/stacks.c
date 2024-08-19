/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:21:00 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/19 14:12:12 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"
#include "util.h"

bool	input_to_stacks(t_stacks *s, size_t num_items, char **item_strs)
{
	int		value;
	size_t	item_idx;
	size_t	scan_idx;

	s->a = circ_alloc(num_items);
	s->b = circ_alloc(num_items);
	if (!s->a || !s->b)
		return (false);
	item_idx = 0;
	while (item_idx < num_items)
	{
		if (!parse_int(item_strs[item_idx], &value))
			return (false);
		scan_idx = 0;
		while (scan_idx < item_idx)
			if (value == *circ_ptr(s->a, scan_idx++))
				return (false);
		circ_push_back(s->a, value);
		item_idx++;
	}
	return (true);
}
