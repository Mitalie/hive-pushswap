/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_pushpop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:34:01 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/23 16:58:39 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circ.h"

#include "circ_internal.h"

void	circ_push_back(t_circ *c, int v)
{
	c->arr[c->end] = v;
	c->end = (c->end + 1) % c->size;
	c->count++;
}

void	circ_push_front(t_circ *c, int v)
{
	c->start = (c->start - 1 + c->size) % c->size;
	c->arr[c->start] = v;
	c->count++;
}

int	circ_pop_back(t_circ *c)
{
	c->end = (c->end - 1 + c->size) % c->size;
	c->count--;
	return (c->arr[c->end]);
}

int	circ_pop_front(t_circ *c)
{
	int	tmp;

	tmp = c->arr[c->start];
	c->start = (c->start + 1) % c->size;
	c->count--;
	return (tmp);
}
