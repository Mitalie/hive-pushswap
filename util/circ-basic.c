/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ-basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:19:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/15 12:20:05 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circ.h"
#include <assert.h>

void	circ_push(t_circular *c, int v)
{
	assert(c->arr);
	assert(c->count < c->size);
	c->arr[c->end] = v;
	c->end = (c->end + 1) % c->size;
	c->count++;
}

int	circ_pop(t_circular *c)
{
	assert(c->arr);
	assert(c->count > 0);
	c->end = (c->end - 1 + c->size) % c->size;
	c->count--;
	return (c->arr[c->end]);
}

void	circ_unshift(t_circular *c, int v)
{
	assert(c->arr);
	assert(c->count < c->size);
	c->start = (c->start - 1 + c->size) % c->size;
	c->arr[c->start] = v;
	c->count++;
}

int	circ_shift(t_circular *c)
{
	int	tmp;

	assert(c->arr);
	assert(c->count > 0);
	tmp = c->arr[c->start];
	c->start = (c->start + 1) % c->size;
	c->count--;
	return (tmp);
}
