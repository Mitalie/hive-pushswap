/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ-extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:20:20 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/15 12:21:38 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circ.h"
#include <assert.h>

void	circ_swap_top(t_circular *c)
{
	size_t	last;
	size_t	second;
	int		tmp;

	assert(c->arr);
	assert(c->count >= 2);
	last = (c->end - 1 + c->size) % c->size;
	second = (c->end - 2 + c->size) % c->size;
	tmp = c->arr[last];
	c->arr[last] = c->arr[second];
	c->arr[second] = tmp;
}

int	circ_peek_top(t_circular *c)
{
	assert(c->arr);
	assert(c->count > 0);
	return (c->arr[(c->end - 1 + c->size) % c->size]);
}

int	circ_peek_bottom(t_circular *c)
{
	assert(c->arr);
	assert(c->count > 0);
	return (c->arr[c->start]);
}

/* pop + unshift */
void	circ_rotate(t_circular *c)
{
	assert(c->arr);
	c->start = (c->start - 1 + c->size) % c->size;
	c->end = (c->end - 1 + c->size) % c->size;
	c->arr[c->start] = c->arr[c->end];
}

/* shift + push */
void	circ_revrotate(t_circular *c)
{
	assert(c->arr);
	c->arr[c->end] = c->arr[c->start];
	c->start = (c->start + 1) % c->size;
	c->end = (c->end + 1) % c->size;
}
