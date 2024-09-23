/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:46:59 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/23 16:49:51 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRC_H
# define CIRC_H

# include <stddef.h>

/*
	Circular array, supporting random access and push/pop at both ends.
*/
typedef struct s_circ	t_circ;

/*
	Allocates and initializes a new `t_circ` with a maximum capacity of `size`
	entries. The returned pointer must be released with `free`.
*/
t_circ	*circ_alloc(size_t size);

/*
	Random access to entries in a `t_circ`. Index 0 is the element in the front
	and the index (length - 1) is the element at the back of the array. The
	returned pointer can be used for both read and write, but pointer arithmetic
	is not safe because caller doesn't know how the indices relate to the bounds
	of the internal buffer.
*/
int		*circ_ptr(t_circ *c, size_t idx);

size_t	circ_len(t_circ *c);
void	circ_push_back(t_circ *c, int v);
void	circ_push_front(t_circ *c, int v);
int		circ_pop_back(t_circ *c);
int		circ_pop_front(t_circ *c);
int		circ_peek_back(t_circ *c);
int		circ_peek_front(t_circ *c);

#endif
