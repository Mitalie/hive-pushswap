/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:10:28 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/15 12:20:07 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circ.h"
#include <assert.h>
#include <stdlib.h>

void	circ_init(t_circular *c, size_t size)
{
	*c = (t_circular){0};
	c->start = 0;
	c->end = 0;
	c->count = 0;
	c->size = size;
	c->arr = malloc(size * sizeof(c->arr[0]));
	assert(c->arr);
}

void	circ_deinit(t_circular *c)
{
	free(c->arr);
	c->arr = 0;
	c->size = 0;
}
