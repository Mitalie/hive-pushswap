/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:33:37 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/14 12:48:30 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circ_internal.h"
#include <assert.h>
#include <stdlib.h>

/* TODO: remove asserts before submission */

t_circ	*circ_alloc(size_t size)
{
	t_circ	*c;

	c = malloc(sizeof(*c) + size * sizeof(c->arr[0]));
	if (c)
	{
		c->start = 0;
		c->end = 0;
		c->count = 0;
		c->size = size;
	}
	return (c);
}

int	*circ_ptr(t_circ *c, size_t idx)
{
	assert(idx < c->count);
	return (&c->arr[(c->start + idx) % c->size]);
}
